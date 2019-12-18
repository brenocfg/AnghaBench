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
struct hugetlbfs_fs_context {unsigned int mode; void* min_val_type; void* min_size_opt; int /*<<< orphan*/  hstate; void* nr_inodes; void* max_val_type; void* max_size_opt; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct fs_parse_result {unsigned int uint_32; } ;
struct fs_parameter {int /*<<< orphan*/  key; int /*<<< orphan*/ * string; } ;
struct fs_context {struct hugetlbfs_fs_context* fs_private; } ;

/* Variables and functions */
 int EINVAL ; 
#define  Opt_gid 134 
#define  Opt_min_size 133 
#define  Opt_mode 132 
#define  Opt_nr_inodes 131 
#define  Opt_pagesize 130 
#define  Opt_size 129 
#define  Opt_uid 128 
 void* SIZE_PERCENT ; 
 void* SIZE_STD ; 
 int /*<<< orphan*/  current_user_ns () ; 
 int fs_parse (struct fs_context*,int /*<<< orphan*/ *,struct fs_parameter*,struct fs_parse_result*) ; 
 int /*<<< orphan*/  gid_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hugetlb_fs_parameters ; 
 int invalf (struct fs_context*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdigit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_kgid (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  make_kuid (int /*<<< orphan*/ ,unsigned int) ; 
 void* memparse (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long) ; 
 int /*<<< orphan*/  size_to_hstate (unsigned long) ; 
 int /*<<< orphan*/  uid_valid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hugetlbfs_parse_param(struct fs_context *fc, struct fs_parameter *param)
{
	struct hugetlbfs_fs_context *ctx = fc->fs_private;
	struct fs_parse_result result;
	char *rest;
	unsigned long ps;
	int opt;

	opt = fs_parse(fc, &hugetlb_fs_parameters, param, &result);
	if (opt < 0)
		return opt;

	switch (opt) {
	case Opt_uid:
		ctx->uid = make_kuid(current_user_ns(), result.uint_32);
		if (!uid_valid(ctx->uid))
			goto bad_val;
		return 0;

	case Opt_gid:
		ctx->gid = make_kgid(current_user_ns(), result.uint_32);
		if (!gid_valid(ctx->gid))
			goto bad_val;
		return 0;

	case Opt_mode:
		ctx->mode = result.uint_32 & 01777U;
		return 0;

	case Opt_size:
		/* memparse() will accept a K/M/G without a digit */
		if (!isdigit(param->string[0]))
			goto bad_val;
		ctx->max_size_opt = memparse(param->string, &rest);
		ctx->max_val_type = SIZE_STD;
		if (*rest == '%')
			ctx->max_val_type = SIZE_PERCENT;
		return 0;

	case Opt_nr_inodes:
		/* memparse() will accept a K/M/G without a digit */
		if (!isdigit(param->string[0]))
			goto bad_val;
		ctx->nr_inodes = memparse(param->string, &rest);
		return 0;

	case Opt_pagesize:
		ps = memparse(param->string, &rest);
		ctx->hstate = size_to_hstate(ps);
		if (!ctx->hstate) {
			pr_err("Unsupported page size %lu MB\n", ps >> 20);
			return -EINVAL;
		}
		return 0;

	case Opt_min_size:
		/* memparse() will accept a K/M/G without a digit */
		if (!isdigit(param->string[0]))
			goto bad_val;
		ctx->min_size_opt = memparse(param->string, &rest);
		ctx->min_val_type = SIZE_STD;
		if (*rest == '%')
			ctx->min_val_type = SIZE_PERCENT;
		return 0;

	default:
		return -EINVAL;
	}

bad_val:
	return invalf(fc, "hugetlbfs: Bad value '%s' for mount option '%s'\n",
		      param->string, param->key);
}