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
struct nilfs_palloc_req {int /*<<< orphan*/  pr_entry_bh; int /*<<< orphan*/  pr_entry_nr; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int nilfs_palloc_get_entry_block (struct inode*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nilfs_dat_prepare_entry(struct inode *dat,
				   struct nilfs_palloc_req *req, int create)
{
	return nilfs_palloc_get_entry_block(dat, req->pr_entry_nr,
					    create, &req->pr_entry_bh);
}