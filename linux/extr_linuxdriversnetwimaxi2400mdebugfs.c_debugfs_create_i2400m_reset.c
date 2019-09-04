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
struct i2400m {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* debugfs_create_file (char const*,int,struct dentry*,struct i2400m*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_i2400m_reset ; 

__attribute__((used)) static
struct dentry *debugfs_create_i2400m_reset(
	const char *name, struct dentry *parent, struct i2400m *i2400m)
{
	return debugfs_create_file(name, 0200, parent, i2400m,
				   &fops_i2400m_reset);
}