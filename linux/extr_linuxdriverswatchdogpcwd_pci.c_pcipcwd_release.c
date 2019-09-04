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
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int expect_release ; 
 int /*<<< orphan*/  is_active ; 
 int /*<<< orphan*/  pcipcwd_keepalive () ; 
 int /*<<< orphan*/  pcipcwd_stop () ; 
 int /*<<< orphan*/  pr_crit (char*) ; 

__attribute__((used)) static int pcipcwd_release(struct inode *inode, struct file *file)
{
	/*
	 *      Shut off the timer.
	 */
	if (expect_release == 42) {
		pcipcwd_stop();
	} else {
		pr_crit("Unexpected close, not stopping watchdog!\n");
		pcipcwd_keepalive();
	}
	expect_release = 0;
	clear_bit(0, &is_active);
	return 0;
}