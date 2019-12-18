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
struct fs_context {int dummy; } ;
struct cgroup_fs_context {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  apply_cgroup_root_flags (int /*<<< orphan*/ ) ; 
 struct cgroup_fs_context* cgroup_fc2context (struct fs_context*) ; 

__attribute__((used)) static int cgroup_reconfigure(struct fs_context *fc)
{
	struct cgroup_fs_context *ctx = cgroup_fc2context(fc);

	apply_cgroup_root_flags(ctx->flags);
	return 0;
}