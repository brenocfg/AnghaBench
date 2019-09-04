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
 struct dentry* debugfs_create_file (char const*,int /*<<< orphan*/ ,struct dentry*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_errno ; 

__attribute__((used)) static struct dentry *debugfs_create_errno(const char *name, umode_t mode,
				struct dentry *parent, int *value)
{
	return debugfs_create_file(name, mode, parent, value, &fops_errno);
}