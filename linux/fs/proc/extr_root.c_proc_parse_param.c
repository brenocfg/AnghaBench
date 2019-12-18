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
struct proc_fs_context {int mask; int /*<<< orphan*/  hidepid; int /*<<< orphan*/  gid; } ;
struct fs_parse_result {int /*<<< orphan*/  uint_32; } ;
struct fs_parameter {int dummy; } ;
struct fs_context {struct proc_fs_context* fs_private; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HIDEPID_INVISIBLE ; 
 int /*<<< orphan*/  HIDEPID_OFF ; 
#define  Opt_gid 129 
#define  Opt_hidepid 128 
 int fs_parse (struct fs_context*,int /*<<< orphan*/ *,struct fs_parameter*,struct fs_parse_result*) ; 
 int invalf (struct fs_context*,char*) ; 
 int /*<<< orphan*/  proc_fs_parameters ; 

__attribute__((used)) static int proc_parse_param(struct fs_context *fc, struct fs_parameter *param)
{
	struct proc_fs_context *ctx = fc->fs_private;
	struct fs_parse_result result;
	int opt;

	opt = fs_parse(fc, &proc_fs_parameters, param, &result);
	if (opt < 0)
		return opt;

	switch (opt) {
	case Opt_gid:
		ctx->gid = result.uint_32;
		break;

	case Opt_hidepid:
		ctx->hidepid = result.uint_32;
		if (ctx->hidepid < HIDEPID_OFF ||
		    ctx->hidepid > HIDEPID_INVISIBLE)
			return invalf(fc, "proc: hidepid value must be between 0 and 2.\n");
		break;

	default:
		return -EINVAL;
	}

	ctx->mask |= 1 << opt;
	return 0;
}