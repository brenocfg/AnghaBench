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
typedef  int /*<<< orphan*/  umode_t ;
struct file_operations {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* __debugfs_create_file (char const*,int /*<<< orphan*/ ,struct dentry*,void*,int /*<<< orphan*/ *,struct file_operations const*) ; 
 int /*<<< orphan*/  debugfs_full_proxy_file_operations ; 
 int /*<<< orphan*/  debugfs_noop_file_operations ; 

struct dentry *debugfs_create_file(const char *name, umode_t mode,
				   struct dentry *parent, void *data,
				   const struct file_operations *fops)
{

	return __debugfs_create_file(name, mode, parent, data,
				fops ? &debugfs_full_proxy_file_operations :
					&debugfs_noop_file_operations,
				fops);
}