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
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* debugfs_create_mode_unsafe (char const*,int /*<<< orphan*/ ,struct dentry*,unsigned long*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_ulong ; 
 int /*<<< orphan*/  fops_ulong_ro ; 
 int /*<<< orphan*/  fops_ulong_wo ; 

struct dentry *debugfs_create_ulong(const char *name, umode_t mode,
				    struct dentry *parent, unsigned long *value)
{
	return debugfs_create_mode_unsafe(name, mode, parent, value,
					&fops_ulong, &fops_ulong_ro,
					&fops_ulong_wo);
}