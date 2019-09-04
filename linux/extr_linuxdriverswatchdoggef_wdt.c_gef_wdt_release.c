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
 int /*<<< orphan*/  GEF_WDOG_FLAG_OPENED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int expect_close ; 
 int /*<<< orphan*/  gef_wdt_handler_disable () ; 
 int /*<<< orphan*/  gef_wdt_service () ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  wdt_flags ; 

__attribute__((used)) static int gef_wdt_release(struct inode *inode, struct file *file)
{
	if (expect_close == 42)
		gef_wdt_handler_disable();
	else {
		pr_crit("unexpected close, not stopping timer!\n");
		gef_wdt_service();
	}
	expect_close = 0;

	clear_bit(GEF_WDOG_FLAG_OPENED, &wdt_flags);

	return 0;
}