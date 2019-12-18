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
struct hugetlbfs_fs_context {scalar_t__ max_hpages; scalar_t__ max_val_type; scalar_t__ min_hpages; scalar_t__ min_val_type; int /*<<< orphan*/  min_size_opt; int /*<<< orphan*/  hstate; int /*<<< orphan*/  max_size_opt; } ;
struct fs_context {struct hugetlbfs_fs_context* fs_private; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NO_SIZE ; 
 void* hugetlbfs_size_to_hpages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int hugetlbfs_validate(struct fs_context *fc)
{
	struct hugetlbfs_fs_context *ctx = fc->fs_private;

	/*
	 * Use huge page pool size (in hstate) to convert the size
	 * options to number of huge pages.  If NO_SIZE, -1 is returned.
	 */
	ctx->max_hpages = hugetlbfs_size_to_hpages(ctx->hstate,
						   ctx->max_size_opt,
						   ctx->max_val_type);
	ctx->min_hpages = hugetlbfs_size_to_hpages(ctx->hstate,
						   ctx->min_size_opt,
						   ctx->min_val_type);

	/*
	 * If max_size was specified, then min_size must be smaller
	 */
	if (ctx->max_val_type > NO_SIZE &&
	    ctx->min_hpages > ctx->max_hpages) {
		pr_err("Minimum size can not be greater than maximum size\n");
		return -EINVAL;
	}

	return 0;
}