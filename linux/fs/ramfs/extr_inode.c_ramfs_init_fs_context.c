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
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;
struct ramfs_fs_info {TYPE_1__ mount_opts; } ;
struct fs_context {int /*<<< orphan*/ * ops; struct ramfs_fs_info* s_fs_info; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RAMFS_DEFAULT_MODE ; 
 struct ramfs_fs_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ramfs_context_ops ; 

int ramfs_init_fs_context(struct fs_context *fc)
{
	struct ramfs_fs_info *fsi;

	fsi = kzalloc(sizeof(*fsi), GFP_KERNEL);
	if (!fsi)
		return -ENOMEM;

	fsi->mount_opts.mode = RAMFS_DEFAULT_MODE;
	fc->s_fs_info = fsi;
	fc->ops = &ramfs_context_ops;
	return 0;
}