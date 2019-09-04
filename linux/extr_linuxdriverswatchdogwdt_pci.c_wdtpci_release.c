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
 int expect_close ; 
 int /*<<< orphan*/  open_lock ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  wdtpci_ping () ; 
 int /*<<< orphan*/  wdtpci_stop () ; 

__attribute__((used)) static int wdtpci_release(struct inode *inode, struct file *file)
{
	if (expect_close == 42) {
		wdtpci_stop();
	} else {
		pr_crit("Unexpected close, not stopping timer!\n");
		wdtpci_ping();
	}
	expect_close = 0;
	clear_bit(0, &open_lock);
	return 0;
}