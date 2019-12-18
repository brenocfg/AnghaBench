#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  symbol_name; } ;
struct fei_attr {TYPE_1__ kp; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* debugfs_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 int /*<<< orphan*/  fei_debugfs_dir ; 

__attribute__((used)) static void fei_debugfs_remove_attr(struct fei_attr *attr)
{
	struct dentry *dir;

	dir = debugfs_lookup(attr->kp.symbol_name, fei_debugfs_dir);
	debugfs_remove_recursive(dir);
}