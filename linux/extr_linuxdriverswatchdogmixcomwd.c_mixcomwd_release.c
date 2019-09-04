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
 int EBUSY ; 
 int HZ ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int expect_close ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mixcomwd_opened ; 
 int /*<<< orphan*/  mixcomwd_timer ; 
 int mixcomwd_timer_alive ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int mixcomwd_release(struct inode *inode, struct file *file)
{
	if (expect_close == 42) {
		if (mixcomwd_timer_alive) {
			pr_err("release called while internal timer alive\n");
			return -EBUSY;
		}
		mixcomwd_timer_alive = 1;
		mod_timer(&mixcomwd_timer, jiffies + 5 * HZ);
	} else
		pr_crit("WDT device closed unexpectedly.  WDT will not stop!\n");

	clear_bit(0, &mixcomwd_opened);
	expect_close = 0;
	return 0;
}