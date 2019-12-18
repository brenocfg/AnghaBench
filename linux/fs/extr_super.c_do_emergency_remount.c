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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __iterate_supers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_emergency_remount_callback ; 
 int /*<<< orphan*/  kfree (struct work_struct*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void do_emergency_remount(struct work_struct *work)
{
	__iterate_supers(do_emergency_remount_callback);
	kfree(work);
	printk("Emergency Remount complete\n");
}