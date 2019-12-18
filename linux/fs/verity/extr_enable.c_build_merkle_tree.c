#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct merkle_tree_params {int block_size; int log_blocksize; unsigned int num_levels; int hashes_per_block; int log_arity; int /*<<< orphan*/  digest_size; TYPE_1__* hash_alg; } ;
struct inode {int i_size; } ;
struct ahash_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tfm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ahash_request* ahash_request_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahash_request_free (struct ahash_request*) ; 
 int build_merkle_tree_level (struct inode*,unsigned int,int,struct merkle_tree_params const*,int /*<<< orphan*/ *,struct ahash_request*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_merkle_tree(struct inode *inode,
			     const struct merkle_tree_params *params,
			     u8 *root_hash)
{
	u8 *pending_hashes;
	struct ahash_request *req;
	u64 blocks;
	unsigned int level;
	int err = -ENOMEM;

	if (inode->i_size == 0) {
		/* Empty file is a special case; root hash is all 0's */
		memset(root_hash, 0, params->digest_size);
		return 0;
	}

	pending_hashes = kmalloc(params->block_size, GFP_KERNEL);
	req = ahash_request_alloc(params->hash_alg->tfm, GFP_KERNEL);
	if (!pending_hashes || !req)
		goto out;

	/*
	 * Build each level of the Merkle tree, starting at the leaf level
	 * (level 0) and ascending to the root node (level 'num_levels - 1').
	 * Then at the end (level 'num_levels'), calculate the root hash.
	 */
	blocks = (inode->i_size + params->block_size - 1) >>
		 params->log_blocksize;
	for (level = 0; level <= params->num_levels; level++) {
		err = build_merkle_tree_level(inode, level, blocks, params,
					      pending_hashes, req);
		if (err)
			goto out;
		blocks = (blocks + params->hashes_per_block - 1) >>
			 params->log_arity;
	}
	memcpy(root_hash, pending_hashes, params->digest_size);
	err = 0;
out:
	kfree(pending_hashes);
	ahash_request_free(req);
	return err;
}