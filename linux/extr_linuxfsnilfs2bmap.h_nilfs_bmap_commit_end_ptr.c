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
union nilfs_bmap_ptr_req {int /*<<< orphan*/  bpr_req; } ;
struct nilfs_bmap {scalar_t__ b_ptr_type; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 scalar_t__ NILFS_BMAP_PTR_VS ; 
 int /*<<< orphan*/  nilfs_dat_commit_end (struct inode*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void nilfs_bmap_commit_end_ptr(struct nilfs_bmap *bmap,
					     union nilfs_bmap_ptr_req *req,
					     struct inode *dat)
{
	if (dat)
		nilfs_dat_commit_end(dat, &req->bpr_req,
				     bmap->b_ptr_type == NILFS_BMAP_PTR_VS);
}