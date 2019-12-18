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
union nilfs_bmap_ptr_req {scalar_t__ bpr_ptr; } ;
struct nilfs_bmap_stats {scalar_t__ bs_nblocks; } ;
struct nilfs_bmap {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 scalar_t__ NILFS_BMAP_USE_VBN (struct nilfs_bmap*) ; 
 int /*<<< orphan*/  nilfs_bmap_abort_alloc_ptr (struct nilfs_bmap*,union nilfs_bmap_ptr_req*,struct inode*) ; 
 struct inode* nilfs_bmap_get_dat (struct nilfs_bmap*) ; 
 int nilfs_bmap_prepare_alloc_ptr (struct nilfs_bmap*,union nilfs_bmap_ptr_req*,struct inode*) ; 
 scalar_t__ nilfs_btree_find_target_v (struct nilfs_bmap*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nilfs_btree_get_new_block (struct nilfs_bmap*,scalar_t__,struct buffer_head**) ; 

__attribute__((used)) static int
nilfs_btree_prepare_convert_and_insert(struct nilfs_bmap *btree, __u64 key,
				       union nilfs_bmap_ptr_req *dreq,
				       union nilfs_bmap_ptr_req *nreq,
				       struct buffer_head **bhp,
				       struct nilfs_bmap_stats *stats)
{
	struct buffer_head *bh;
	struct inode *dat = NULL;
	int ret;

	stats->bs_nblocks = 0;

	/* for data */
	/* cannot find near ptr */
	if (NILFS_BMAP_USE_VBN(btree)) {
		dreq->bpr_ptr = nilfs_btree_find_target_v(btree, NULL, key);
		dat = nilfs_bmap_get_dat(btree);
	}

	ret = nilfs_bmap_prepare_alloc_ptr(btree, dreq, dat);
	if (ret < 0)
		return ret;

	*bhp = NULL;
	stats->bs_nblocks++;
	if (nreq != NULL) {
		nreq->bpr_ptr = dreq->bpr_ptr + 1;
		ret = nilfs_bmap_prepare_alloc_ptr(btree, nreq, dat);
		if (ret < 0)
			goto err_out_dreq;

		ret = nilfs_btree_get_new_block(btree, nreq->bpr_ptr, &bh);
		if (ret < 0)
			goto err_out_nreq;

		*bhp = bh;
		stats->bs_nblocks++;
	}

	/* success */
	return 0;

	/* error */
 err_out_nreq:
	nilfs_bmap_abort_alloc_ptr(btree, nreq, dat);
 err_out_dreq:
	nilfs_bmap_abort_alloc_ptr(btree, dreq, dat);
	stats->bs_nblocks = 0;
	return ret;

}