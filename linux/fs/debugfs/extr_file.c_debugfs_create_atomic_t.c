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
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 struct dentry* debugfs_create_mode_unsafe (char const*,int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_atomic_t ; 
 int /*<<< orphan*/  fops_atomic_t_ro ; 
 int /*<<< orphan*/  fops_atomic_t_wo ; 

struct dentry *debugfs_create_atomic_t(const char *name, umode_t mode,
				 struct dentry *parent, atomic_t *value)
{
	return debugfs_create_mode_unsafe(name, mode, parent, value,
					&fops_atomic_t, &fops_atomic_t_ro,
					&fops_atomic_t_wo);
}