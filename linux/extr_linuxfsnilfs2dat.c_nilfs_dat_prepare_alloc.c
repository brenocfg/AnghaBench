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
 int nilfs_dat_prepare_entry (struct inode*,struct nilfs_palloc_req*,int) ; 
 int /*<<< orphan*/  nilfs_palloc_abort_alloc_entry (struct inode*,struct nilfs_palloc_req*) ; 
 int nilfs_palloc_prepare_alloc_entry (struct inode*,struct nilfs_palloc_req*) ; 

int nilfs_dat_prepare_alloc(struct inode *dat, struct nilfs_palloc_req *req)
{
	int ret;

	ret = nilfs_palloc_prepare_alloc_entry(dat, req);
	if (ret < 0)
		return ret;

	ret = nilfs_dat_prepare_entry(dat, req, 1);
	if (ret < 0)
		nilfs_palloc_abort_alloc_entry(dat, req);

	return ret;
}