#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_2__* s_op; } ;
struct legacy_fs_context {int /*<<< orphan*/ * legacy_data; } ;
struct fs_context {int /*<<< orphan*/  sb_flags; TYPE_1__* root; struct legacy_fs_context* fs_private; } ;
struct TYPE_4__ {int (* remount_fs ) (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {struct super_block* d_sb; } ;

/* Variables and functions */
 int stub1 (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int legacy_reconfigure(struct fs_context *fc)
{
	struct legacy_fs_context *ctx = fc->fs_private;
	struct super_block *sb = fc->root->d_sb;

	if (!sb->s_op->remount_fs)
		return 0;

	return sb->s_op->remount_fs(sb, &fc->sb_flags,
				    ctx ? ctx->legacy_data : NULL);
}