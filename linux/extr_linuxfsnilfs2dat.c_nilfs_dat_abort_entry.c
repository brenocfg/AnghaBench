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
struct nilfs_palloc_req {int /*<<< orphan*/  pr_entry_bh; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nilfs_dat_abort_entry(struct inode *dat,
				  struct nilfs_palloc_req *req)
{
	brelse(req->pr_entry_bh);
}