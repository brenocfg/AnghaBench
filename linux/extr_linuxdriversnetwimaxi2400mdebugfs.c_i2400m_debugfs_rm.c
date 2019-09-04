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
struct i2400m {int /*<<< orphan*/  debugfs_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 

void i2400m_debugfs_rm(struct i2400m *i2400m)
{
	debugfs_remove_recursive(i2400m->debugfs_dentry);
}