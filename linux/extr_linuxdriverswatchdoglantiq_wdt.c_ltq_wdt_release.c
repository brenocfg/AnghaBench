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
 int /*<<< orphan*/  ltq_wdt_disable () ; 
 int /*<<< orphan*/  ltq_wdt_in_use ; 
 scalar_t__ ltq_wdt_ok_to_close ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int
ltq_wdt_release(struct inode *inode, struct file *file)
{
	if (ltq_wdt_ok_to_close)
		ltq_wdt_disable();
	else
		pr_err("watchdog closed without warning\n");
	ltq_wdt_ok_to_close = 0;
	clear_bit(0, &ltq_wdt_in_use);

	return 0;
}