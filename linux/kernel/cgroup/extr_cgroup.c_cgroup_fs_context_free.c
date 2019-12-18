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
struct cgroup_fs_context {int /*<<< orphan*/  ns; struct cgroup_fs_context* release_agent; struct cgroup_fs_context* name; } ;

/* Variables and functions */
 struct cgroup_fs_context* cgroup_fc2context (struct fs_context*) ; 
 int /*<<< orphan*/  kernfs_free_fs_context (struct fs_context*) ; 
 int /*<<< orphan*/  kfree (struct cgroup_fs_context*) ; 
 int /*<<< orphan*/  put_cgroup_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cgroup_fs_context_free(struct fs_context *fc)
{
	struct cgroup_fs_context *ctx = cgroup_fc2context(fc);

	kfree(ctx->name);
	kfree(ctx->release_agent);
	put_cgroup_ns(ctx->ns);
	kernfs_free_fs_context(fc);
	kfree(ctx);
}