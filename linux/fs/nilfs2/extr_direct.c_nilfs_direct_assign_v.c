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
union nilfs_bmap_ptr_req {int /*<<< orphan*/  bpr_req; int /*<<< orphan*/  bpr_ptr; } ;
struct TYPE_2__ {void* bi_blkoff; void* bi_vblocknr; } ;
union nilfs_binfo {TYPE_1__ bi_v; } ;
struct nilfs_bmap {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct inode* nilfs_bmap_get_dat (struct nilfs_bmap*) ; 
 int /*<<< orphan*/  nilfs_dat_commit_start (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nilfs_dat_prepare_start (struct inode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_direct_assign_v(struct nilfs_bmap *direct,
				 __u64 key, __u64 ptr,
				 struct buffer_head **bh,
				 sector_t blocknr,
				 union nilfs_binfo *binfo)
{
	struct inode *dat = nilfs_bmap_get_dat(direct);
	union nilfs_bmap_ptr_req req;
	int ret;

	req.bpr_ptr = ptr;
	ret = nilfs_dat_prepare_start(dat, &req.bpr_req);
	if (!ret) {
		nilfs_dat_commit_start(dat, &req.bpr_req, blocknr);
		binfo->bi_v.bi_vblocknr = cpu_to_le64(ptr);
		binfo->bi_v.bi_blkoff = cpu_to_le64(key);
	}
	return ret;
}