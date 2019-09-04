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
struct writeback_control {int dummy; } ;
struct page {TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int writepage_nounlock (struct page*,struct writeback_control*) ; 

__attribute__((used)) static int ceph_writepage(struct page *page, struct writeback_control *wbc)
{
	int err;
	struct inode *inode = page->mapping->host;
	BUG_ON(!inode);
	ihold(inode);
	err = writepage_nounlock(page, wbc);
	if (err == -ERESTARTSYS) {
		/* direct memory reclaimer was killed by SIGKILL. return 0
		 * to prevent caller from setting mapping/page error */
		err = 0;
	}
	unlock_page(page);
	iput(inode);
	return err;
}