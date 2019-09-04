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
struct nfs_lock_context {int /*<<< orphan*/  io_count; int /*<<< orphan*/  list; int /*<<< orphan*/  lockowner; int /*<<< orphan*/  count; } ;
struct TYPE_2__ {int /*<<< orphan*/  files; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void nfs_init_lock_context(struct nfs_lock_context *l_ctx)
{
	refcount_set(&l_ctx->count, 1);
	l_ctx->lockowner = current->files;
	INIT_LIST_HEAD(&l_ctx->list);
	atomic_set(&l_ctx->io_count, 0);
}