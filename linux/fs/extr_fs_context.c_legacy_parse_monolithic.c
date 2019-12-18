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
struct legacy_fs_context {scalar_t__ param_type; void* legacy_data; } ;
struct fs_context {int /*<<< orphan*/  security; TYPE_1__* fs_type; struct legacy_fs_context* fs_private; } ;
struct TYPE_2__ {int fs_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int FS_BINARY_MOUNTDATA ; 
 scalar_t__ LEGACY_FS_MONOLITHIC_PARAMS ; 
 scalar_t__ LEGACY_FS_UNSET_PARAMS ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int security_sb_eat_lsm_opts (void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int legacy_parse_monolithic(struct fs_context *fc, void *data)
{
	struct legacy_fs_context *ctx = fc->fs_private;

	if (ctx->param_type != LEGACY_FS_UNSET_PARAMS) {
		pr_warn("VFS: Can't mix monolithic and individual options\n");
		return -EINVAL;
	}

	ctx->legacy_data = data;
	ctx->param_type = LEGACY_FS_MONOLITHIC_PARAMS;
	if (!ctx->legacy_data)
		return 0;

	if (fc->fs_type->fs_flags & FS_BINARY_MOUNTDATA)
		return 0;
	return security_sb_eat_lsm_opts(ctx->legacy_data, &fc->security);
}