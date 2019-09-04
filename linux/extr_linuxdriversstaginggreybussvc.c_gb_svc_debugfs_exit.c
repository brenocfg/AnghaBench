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
struct gb_svc {int /*<<< orphan*/ * pwrmon_rails; int /*<<< orphan*/  debugfs_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_svc_debugfs_exit(struct gb_svc *svc)
{
	debugfs_remove_recursive(svc->debugfs_dentry);
	kfree(svc->pwrmon_rails);
	svc->pwrmon_rails = NULL;
}