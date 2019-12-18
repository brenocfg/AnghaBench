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
struct page {int dummy; } ;
struct merkle_tree_params {scalar_t__ block_size; unsigned int num_levels; int* level_start; scalar_t__ digest_size; int /*<<< orphan*/  log_blocksize; } ;
struct inode {int /*<<< orphan*/  i_mapping; TYPE_1__* i_sb; } ;
struct fsverity_operations {int (* write_merkle_tree_block ) (struct inode*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ;struct page* (* read_merkle_tree_page ) (struct inode*,int) ;} ;
struct ahash_request {int dummy; } ;
typedef  int pgoff_t ;
struct TYPE_2__ {struct fsverity_operations* s_vop; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct page*) ; 
 scalar_t__ PAGE_SIZE ; 
 int PTR_ERR (struct page*) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ fatal_signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsverity_err (struct inode*,char*,int,int) ; 
 int fsverity_hash_page (struct merkle_tree_params const*,struct inode*,struct ahash_request*,struct page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,unsigned int) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 struct page* read_mapping_page (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct page* stub1 (struct inode*,int) ; 
 int stub2 (struct inode*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int build_merkle_tree_level(struct inode *inode, unsigned int level,
				   u64 num_blocks_to_hash,
				   const struct merkle_tree_params *params,
				   u8 *pending_hashes,
				   struct ahash_request *req)
{
	const struct fsverity_operations *vops = inode->i_sb->s_vop;
	unsigned int pending_size = 0;
	u64 dst_block_num;
	u64 i;
	int err;

	if (WARN_ON(params->block_size != PAGE_SIZE)) /* checked earlier too */
		return -EINVAL;

	if (level < params->num_levels) {
		dst_block_num = params->level_start[level];
	} else {
		if (WARN_ON(num_blocks_to_hash != 1))
			return -EINVAL;
		dst_block_num = 0; /* unused */
	}

	for (i = 0; i < num_blocks_to_hash; i++) {
		struct page *src_page;

		if ((pgoff_t)i % 10000 == 0 || i + 1 == num_blocks_to_hash)
			pr_debug("Hashing block %llu of %llu for level %u\n",
				 i + 1, num_blocks_to_hash, level);

		if (level == 0) {
			/* Leaf: hashing a data block */
			src_page = read_mapping_page(inode->i_mapping, i, NULL);
			if (IS_ERR(src_page)) {
				err = PTR_ERR(src_page);
				fsverity_err(inode,
					     "Error %d reading data page %llu",
					     err, i);
				return err;
			}
		} else {
			/* Non-leaf: hashing hash block from level below */
			src_page = vops->read_merkle_tree_page(inode,
					params->level_start[level - 1] + i);
			if (IS_ERR(src_page)) {
				err = PTR_ERR(src_page);
				fsverity_err(inode,
					     "Error %d reading Merkle tree page %llu",
					     err, params->level_start[level - 1] + i);
				return err;
			}
		}

		err = fsverity_hash_page(params, inode, req, src_page,
					 &pending_hashes[pending_size]);
		put_page(src_page);
		if (err)
			return err;
		pending_size += params->digest_size;

		if (level == params->num_levels) /* Root hash? */
			return 0;

		if (pending_size + params->digest_size > params->block_size ||
		    i + 1 == num_blocks_to_hash) {
			/* Flush the pending hash block */
			memset(&pending_hashes[pending_size], 0,
			       params->block_size - pending_size);
			err = vops->write_merkle_tree_block(inode,
					pending_hashes,
					dst_block_num,
					params->log_blocksize);
			if (err) {
				fsverity_err(inode,
					     "Error %d writing Merkle tree block %llu",
					     err, dst_block_num);
				return err;
			}
			dst_block_num++;
			pending_size = 0;
		}

		if (fatal_signal_pending(current))
			return -EINTR;
		cond_resched();
	}
	return 0;
}