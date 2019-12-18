#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dentry {int dummy; } ;
struct TYPE_3__ {struct dentry* mnt_root; } ;

/* Variables and functions */
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  configfs_fs_type ; 
 int /*<<< orphan*/  configfs_mnt_count ; 
 TYPE_1__* configfs_mount ; 
 int simple_pin_fs (int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *) ; 

struct dentry *configfs_pin_fs(void)
{
	int err = simple_pin_fs(&configfs_fs_type, &configfs_mount,
			     &configfs_mnt_count);
	return err ? ERR_PTR(err) : configfs_mount->mnt_root;
}