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
struct dentry {int dummy; } ;

/* Variables and functions */
 int S_IFREG ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fault_disconnect_fops ; 

__attribute__((used)) static struct dentry *
inject_fault_dir(struct dentry *topdir)
{
	struct dentry *faultdir;

	faultdir = debugfs_create_dir("inject_fault", topdir);
	if (!faultdir)
		return NULL;

	if (!debugfs_create_file("disconnect", S_IFREG | 0400, faultdir,
				 NULL, &fault_disconnect_fops))
		return NULL;

	return faultdir;
}