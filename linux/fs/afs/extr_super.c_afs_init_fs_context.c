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
struct fs_context {int /*<<< orphan*/ * ops; struct afs_fs_context* fs_private; int /*<<< orphan*/  net_ns; } ;
struct afs_fs_context {struct afs_cell* cell; int /*<<< orphan*/  net; int /*<<< orphan*/  type; } ;
struct afs_cell {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFSVL_ROVOL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct afs_cell*) ; 
 int /*<<< orphan*/  afs_context_ops ; 
 struct afs_cell* afs_lookup_cell_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_net (int /*<<< orphan*/ ) ; 
 struct afs_fs_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int afs_init_fs_context(struct fs_context *fc)
{
	struct afs_fs_context *ctx;
	struct afs_cell *cell;

	ctx = kzalloc(sizeof(struct afs_fs_context), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->type = AFSVL_ROVOL;
	ctx->net = afs_net(fc->net_ns);

	/* Default to the workstation cell. */
	rcu_read_lock();
	cell = afs_lookup_cell_rcu(ctx->net, NULL, 0);
	rcu_read_unlock();
	if (IS_ERR(cell))
		cell = NULL;
	ctx->cell = cell;

	fc->fs_private = ctx;
	fc->ops = &afs_context_ops;
	return 0;
}