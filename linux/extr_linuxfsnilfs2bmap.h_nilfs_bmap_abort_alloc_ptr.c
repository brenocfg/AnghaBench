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
struct nilfs_bmap {int /*<<< orphan*/  b_last_allocated_ptr; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nilfs_dat_abort_alloc (struct inode*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void nilfs_bmap_abort_alloc_ptr(struct nilfs_bmap *bmap,
					      union nilfs_bmap_ptr_req *req,
					      struct inode *dat)
{
	if (dat)
		nilfs_dat_abort_alloc(dat, &req->bpr_req);
	else
		bmap->b_last_allocated_ptr--;
}