#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct merkle_tree_params {int digest_size; unsigned int log_blocksize; int block_size; int log_arity; int hashes_per_block; scalar_t__ num_levels; int* level_start; int tree_size; struct fsverity_hash_alg const* hashstate; struct fsverity_hash_alg const* hash_alg; } ;
struct inode {int /*<<< orphan*/  i_size; } ;
struct fsverity_hash_alg {int digest_size; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ FS_VERITY_MAX_LEVELS ; 
 scalar_t__ IS_ERR (struct fsverity_hash_alg const*) ; 
 unsigned int PAGE_SHIFT ; 
 int PTR_ERR (struct fsverity_hash_alg const*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  fsverity_err (struct inode const*,char*,...) ; 
 struct fsverity_hash_alg* fsverity_get_hash_alg (struct inode const*,unsigned int) ; 
 struct fsverity_hash_alg const* fsverity_prepare_hash_state (struct fsverity_hash_alg const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  fsverity_warn (struct inode const*,char*,int,...) ; 
 int ilog2 (int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  kfree (struct fsverity_hash_alg const*) ; 
 int /*<<< orphan*/  memset (struct merkle_tree_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,...) ; 

int fsverity_init_merkle_tree_params(struct merkle_tree_params *params,
				     const struct inode *inode,
				     unsigned int hash_algorithm,
				     unsigned int log_blocksize,
				     const u8 *salt, size_t salt_size)
{
	const struct fsverity_hash_alg *hash_alg;
	int err;
	u64 blocks;
	u64 offset;
	int level;

	memset(params, 0, sizeof(*params));

	hash_alg = fsverity_get_hash_alg(inode, hash_algorithm);
	if (IS_ERR(hash_alg))
		return PTR_ERR(hash_alg);
	params->hash_alg = hash_alg;
	params->digest_size = hash_alg->digest_size;

	params->hashstate = fsverity_prepare_hash_state(hash_alg, salt,
							salt_size);
	if (IS_ERR(params->hashstate)) {
		err = PTR_ERR(params->hashstate);
		params->hashstate = NULL;
		fsverity_err(inode, "Error %d preparing hash state", err);
		goto out_err;
	}

	if (log_blocksize != PAGE_SHIFT) {
		fsverity_warn(inode, "Unsupported log_blocksize: %u",
			      log_blocksize);
		err = -EINVAL;
		goto out_err;
	}
	params->log_blocksize = log_blocksize;
	params->block_size = 1 << log_blocksize;

	if (WARN_ON(!is_power_of_2(params->digest_size))) {
		err = -EINVAL;
		goto out_err;
	}
	if (params->block_size < 2 * params->digest_size) {
		fsverity_warn(inode,
			      "Merkle tree block size (%u) too small for hash algorithm \"%s\"",
			      params->block_size, hash_alg->name);
		err = -EINVAL;
		goto out_err;
	}
	params->log_arity = params->log_blocksize - ilog2(params->digest_size);
	params->hashes_per_block = 1 << params->log_arity;

	pr_debug("Merkle tree uses %s with %u-byte blocks (%u hashes/block), salt=%*phN\n",
		 hash_alg->name, params->block_size, params->hashes_per_block,
		 (int)salt_size, salt);

	/*
	 * Compute the number of levels in the Merkle tree and create a map from
	 * level to the starting block of that level.  Level 'num_levels - 1' is
	 * the root and is stored first.  Level 0 is the level directly "above"
	 * the data blocks and is stored last.
	 */

	/* Compute number of levels and the number of blocks in each level */
	blocks = (inode->i_size + params->block_size - 1) >> log_blocksize;
	pr_debug("Data is %lld bytes (%llu blocks)\n", inode->i_size, blocks);
	while (blocks > 1) {
		if (params->num_levels >= FS_VERITY_MAX_LEVELS) {
			fsverity_err(inode, "Too many levels in Merkle tree");
			err = -EINVAL;
			goto out_err;
		}
		blocks = (blocks + params->hashes_per_block - 1) >>
			 params->log_arity;
		/* temporarily using level_start[] to store blocks in level */
		params->level_start[params->num_levels++] = blocks;
	}

	/* Compute the starting block of each level */
	offset = 0;
	for (level = (int)params->num_levels - 1; level >= 0; level--) {
		blocks = params->level_start[level];
		params->level_start[level] = offset;
		pr_debug("Level %d is %llu blocks starting at index %llu\n",
			 level, blocks, offset);
		offset += blocks;
	}

	params->tree_size = offset << log_blocksize;
	return 0;

out_err:
	kfree(params->hashstate);
	memset(params, 0, sizeof(*params));
	return err;
}