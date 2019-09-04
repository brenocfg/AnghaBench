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
struct nfs_lock_context {int /*<<< orphan*/  io_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int wait_var_event_killable (int /*<<< orphan*/ *,int) ; 

int
nfs_iocounter_wait(struct nfs_lock_context *l_ctx)
{
	return wait_var_event_killable(&l_ctx->io_count,
				       !atomic_read(&l_ctx->io_count));
}