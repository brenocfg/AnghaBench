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
 int /*<<< orphan*/  nilfs_dat_abort_entry (struct inode*,struct nilfs_palloc_req*) ; 
 int /*<<< orphan*/  nilfs_palloc_abort_alloc_entry (struct inode*,struct nilfs_palloc_req*) ; 

void nilfs_dat_abort_alloc(struct inode *dat, struct nilfs_palloc_req *req)
{
	nilfs_dat_abort_entry(dat, req);
	nilfs_palloc_abort_alloc_entry(dat, req);
}