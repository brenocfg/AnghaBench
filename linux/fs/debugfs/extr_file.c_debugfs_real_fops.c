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
struct file_operations {int dummy; } ;
struct file {int dummy; } ;
struct debugfs_fsdata {struct file_operations const* real_fops; } ;
struct TYPE_2__ {struct debugfs_fsdata* d_fsdata; } ;

/* Variables and functions */
 unsigned long DEBUGFS_FSDATA_IS_REAL_FOPS_BIT ; 
 TYPE_1__* F_DENTRY (struct file const*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 

const struct file_operations *debugfs_real_fops(const struct file *filp)
{
	struct debugfs_fsdata *fsd = F_DENTRY(filp)->d_fsdata;

	if ((unsigned long)fsd & DEBUGFS_FSDATA_IS_REAL_FOPS_BIT) {
		/*
		 * Urgh, we've been called w/o a protecting
		 * debugfs_file_get().
		 */
		WARN_ON(1);
		return NULL;
	}

	return fsd->real_fops;
}