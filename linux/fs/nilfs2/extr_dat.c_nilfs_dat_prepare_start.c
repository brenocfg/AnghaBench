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
 int ENOENT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int nilfs_dat_prepare_entry (struct inode*,struct nilfs_palloc_req*,int /*<<< orphan*/ ) ; 

int nilfs_dat_prepare_start(struct inode *dat, struct nilfs_palloc_req *req)
{
	int ret;

	ret = nilfs_dat_prepare_entry(dat, req, 0);
	WARN_ON(ret == -ENOENT);
	return ret;
}