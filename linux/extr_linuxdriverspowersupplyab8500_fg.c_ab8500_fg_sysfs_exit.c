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
struct ab8500_fg {int /*<<< orphan*/  fg_kobject; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ab8500_fg_sysfs_exit(struct ab8500_fg *di)
{
	kobject_del(&di->fg_kobject);
}