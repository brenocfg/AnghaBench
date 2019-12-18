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
struct nilfs_palloc_req {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nilfs_dat_abort_end (struct inode*,struct nilfs_palloc_req*) ; 
 int nilfs_dat_prepare_alloc (struct inode*,struct nilfs_palloc_req*) ; 
 int nilfs_dat_prepare_end (struct inode*,struct nilfs_palloc_req*) ; 

int nilfs_dat_prepare_update(struct inode *dat,
			     struct nilfs_palloc_req *oldreq,
			     struct nilfs_palloc_req *newreq)
{
	int ret;

	ret = nilfs_dat_prepare_end(dat, oldreq);
	if (!ret) {
		ret = nilfs_dat_prepare_alloc(dat, newreq);
		if (ret < 0)
			nilfs_dat_abort_end(dat, oldreq);
	}
	return ret;
}