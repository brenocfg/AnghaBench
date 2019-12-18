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
struct TYPE_2__ {int /*<<< orphan*/  nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir ; 
 int /*<<< orphan*/  of_reconfig_notifier_unregister (int /*<<< orphan*/ *) ; 
 TYPE_1__ reconfig_err_inject ; 

__attribute__((used)) static void err_inject_exit(void)
{
	of_reconfig_notifier_unregister(&reconfig_err_inject.nb);
	debugfs_remove_recursive(dir);
}