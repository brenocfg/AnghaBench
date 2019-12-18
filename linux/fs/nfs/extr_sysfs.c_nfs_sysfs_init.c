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
 int ENOMEM ; 
 int /*<<< orphan*/  fs_kobj ; 
 int /*<<< orphan*/ * kset_create_and_add (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kset_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_client_kobj ; 
 int /*<<< orphan*/ * nfs_client_kset ; 
 int /*<<< orphan*/  nfs_netns_object_alloc (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int nfs_sysfs_init(void)
{
	nfs_client_kset = kset_create_and_add("nfs", NULL, fs_kobj);
	if (!nfs_client_kset)
		return -ENOMEM;
	nfs_client_kobj = nfs_netns_object_alloc("net", nfs_client_kset, NULL);
	if  (!nfs_client_kobj) {
		kset_unregister(nfs_client_kset);
		nfs_client_kset = NULL;
		return -ENOMEM;
	}
	return 0;
}