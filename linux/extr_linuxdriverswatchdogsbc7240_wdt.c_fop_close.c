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
 int /*<<< orphan*/  SBC7240_EXPECT_CLOSE_STATUS_BIT ; 
 int /*<<< orphan*/  SBC7240_OPEN_STATUS_BIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_disable () ; 
 int /*<<< orphan*/  wdt_keepalive () ; 
 int /*<<< orphan*/  wdt_status ; 

__attribute__((used)) static int fop_close(struct inode *inode, struct file *file)
{
	if (test_and_clear_bit(SBC7240_EXPECT_CLOSE_STATUS_BIT, &wdt_status)
	    || !nowayout) {
		wdt_disable();
	} else {
		pr_crit("Unexpected close, not stopping watchdog!\n");
		wdt_keepalive();
	}

	clear_bit(SBC7240_OPEN_STATUS_BIT, &wdt_status);
	return 0;
}