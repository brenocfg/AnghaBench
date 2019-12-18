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
struct fuse_fs_context {int fd_present; int rootmode_present; int user_id_present; int group_id_present; int default_permissions; int allow_other; int /*<<< orphan*/  blksize; int /*<<< orphan*/  is_bdev; int /*<<< orphan*/  max_read; int /*<<< orphan*/  group_id; int /*<<< orphan*/  user_id; int /*<<< orphan*/  rootmode; int /*<<< orphan*/  fd; int /*<<< orphan*/ * subtype; } ;
struct fs_parse_result {int /*<<< orphan*/  uint_32; } ;
struct fs_parameter {int /*<<< orphan*/ * string; } ;
struct fs_context {int /*<<< orphan*/  user_ns; int /*<<< orphan*/ * source; struct fuse_fs_context* fs_private; } ;

/* Variables and functions */
 int EINVAL ; 
#define  OPT_ALLOW_OTHER 137 
#define  OPT_BLKSIZE 136 
#define  OPT_DEFAULT_PERMISSIONS 135 
#define  OPT_FD 134 
#define  OPT_GROUP_ID 133 
#define  OPT_MAX_READ 132 
#define  OPT_ROOTMODE 131 
#define  OPT_SOURCE 130 
#define  OPT_SUBTYPE 129 
#define  OPT_USER_ID 128 
 int fs_parse (struct fs_context*,int /*<<< orphan*/ *,struct fs_parameter*,struct fs_parse_result*) ; 
 int /*<<< orphan*/  fuse_fs_parameters ; 
 int /*<<< orphan*/  fuse_valid_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int invalf (struct fs_context*,char*) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fuse_parse_param(struct fs_context *fc, struct fs_parameter *param)
{
	struct fs_parse_result result;
	struct fuse_fs_context *ctx = fc->fs_private;
	int opt;

	opt = fs_parse(fc, &fuse_fs_parameters, param, &result);
	if (opt < 0)
		return opt;

	switch (opt) {
	case OPT_SOURCE:
		if (fc->source)
			return invalf(fc, "fuse: Multiple sources specified");
		fc->source = param->string;
		param->string = NULL;
		break;

	case OPT_SUBTYPE:
		if (ctx->subtype)
			return invalf(fc, "fuse: Multiple subtypes specified");
		ctx->subtype = param->string;
		param->string = NULL;
		return 0;

	case OPT_FD:
		ctx->fd = result.uint_32;
		ctx->fd_present = 1;
		break;

	case OPT_ROOTMODE:
		if (!fuse_valid_type(result.uint_32))
			return invalf(fc, "fuse: Invalid rootmode");
		ctx->rootmode = result.uint_32;
		ctx->rootmode_present = 1;
		break;

	case OPT_USER_ID:
		ctx->user_id = make_kuid(fc->user_ns, result.uint_32);
		if (!uid_valid(ctx->user_id))
			return invalf(fc, "fuse: Invalid user_id");
		ctx->user_id_present = 1;
		break;

	case OPT_GROUP_ID:
		ctx->group_id = make_kgid(fc->user_ns, result.uint_32);
		if (!gid_valid(ctx->group_id))
			return invalf(fc, "fuse: Invalid group_id");
		ctx->group_id_present = 1;
		break;

	case OPT_DEFAULT_PERMISSIONS:
		ctx->default_permissions = 1;
		break;

	case OPT_ALLOW_OTHER:
		ctx->allow_other = 1;
		break;

	case OPT_MAX_READ:
		ctx->max_read = result.uint_32;
		break;

	case OPT_BLKSIZE:
		if (!ctx->is_bdev)
			return invalf(fc, "fuse: blksize only supported for fuseblk");
		ctx->blksize = result.uint_32;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}