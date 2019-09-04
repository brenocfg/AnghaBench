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
typedef  int /*<<< orphan*/  ulong ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* debugfs_create_file (char const*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wil_fops_ulong ; 

__attribute__((used)) static struct dentry *wil_debugfs_create_ulong(const char *name, umode_t mode,
					       struct dentry *parent,
					       ulong *value)
{
	return debugfs_create_file(name, mode, parent, value, &wil_fops_ulong);
}