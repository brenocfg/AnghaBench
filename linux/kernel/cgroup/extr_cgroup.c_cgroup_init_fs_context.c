#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fs_context {int global; int /*<<< orphan*/  user_ns; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * fs_type; int /*<<< orphan*/ * fs_private; } ;
struct cgroup_fs_context {TYPE_2__* ns; int /*<<< orphan*/  kfc; } ;
struct TYPE_6__ {TYPE_1__* nsproxy; } ;
struct TYPE_5__ {int /*<<< orphan*/  user_ns; } ;
struct TYPE_4__ {TYPE_2__* cgroup_ns; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cgroup1_fs_context_ops ; 
 int /*<<< orphan*/  cgroup2_fs_type ; 
 int /*<<< orphan*/  cgroup_enable_task_cg_lists () ; 
 int /*<<< orphan*/  cgroup_fs_context_ops ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  get_cgroup_ns (TYPE_2__*) ; 
 int /*<<< orphan*/  get_user_ns (int /*<<< orphan*/ ) ; 
 struct cgroup_fs_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_user_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_task_css_set_links ; 

__attribute__((used)) static int cgroup_init_fs_context(struct fs_context *fc)
{
	struct cgroup_fs_context *ctx;

	ctx = kzalloc(sizeof(struct cgroup_fs_context), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	/*
	 * The first time anyone tries to mount a cgroup, enable the list
	 * linking each css_set to its tasks and fix up all existing tasks.
	 */
	if (!use_task_css_set_links)
		cgroup_enable_task_cg_lists();

	ctx->ns = current->nsproxy->cgroup_ns;
	get_cgroup_ns(ctx->ns);
	fc->fs_private = &ctx->kfc;
	if (fc->fs_type == &cgroup2_fs_type)
		fc->ops = &cgroup_fs_context_ops;
	else
		fc->ops = &cgroup1_fs_context_ops;
	put_user_ns(fc->user_ns);
	fc->user_ns = get_user_ns(ctx->ns->user_ns);
	fc->global = true;
	return 0;
}