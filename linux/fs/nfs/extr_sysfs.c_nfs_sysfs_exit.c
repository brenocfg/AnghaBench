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

/* Variables and functions */
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kset_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_client_kobj ; 
 int /*<<< orphan*/  nfs_client_kset ; 

void nfs_sysfs_exit(void)
{
	kobject_put(nfs_client_kobj);
	kset_unregister(nfs_client_kset);
}