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
 struct dentry* debugfs_create_mode_unsafe (char const*,int /*<<< orphan*/ ,struct dentry*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_size_t ; 
 int /*<<< orphan*/  fops_size_t_ro ; 
 int /*<<< orphan*/  fops_size_t_wo ; 

struct dentry *debugfs_create_size_t(const char *name, umode_t mode,
				     struct dentry *parent, size_t *value)
{
	return debugfs_create_mode_unsafe(name, mode, parent, value,
					&fops_size_t, &fops_size_t_ro,
					&fops_size_t_wo);
}