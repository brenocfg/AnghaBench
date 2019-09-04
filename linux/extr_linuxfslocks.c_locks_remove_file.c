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
struct file_lock_context {int /*<<< orphan*/  flc_lock; int /*<<< orphan*/  flc_lease; int /*<<< orphan*/  flc_flock; int /*<<< orphan*/  flc_posix; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_flctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  locks_check_ctx_file_list (struct file*,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* locks_inode (struct file*) ; 
 int /*<<< orphan*/  locks_remove_flock (struct file*,struct file_lock_context*) ; 
 int /*<<< orphan*/  locks_remove_lease (struct file*,struct file_lock_context*) ; 
 int /*<<< orphan*/  locks_remove_posix (struct file*,struct file*) ; 
 struct file_lock_context* smp_load_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void locks_remove_file(struct file *filp)
{
	struct file_lock_context *ctx;

	ctx = smp_load_acquire(&locks_inode(filp)->i_flctx);
	if (!ctx)
		return;

	/* remove any OFD locks */
	locks_remove_posix(filp, filp);

	/* remove flock locks */
	locks_remove_flock(filp, ctx);

	/* remove any leases */
	locks_remove_lease(filp, ctx);

	spin_lock(&ctx->flc_lock);
	locks_check_ctx_file_list(filp, &ctx->flc_posix, "POSIX");
	locks_check_ctx_file_list(filp, &ctx->flc_flock, "FLOCK");
	locks_check_ctx_file_list(filp, &ctx->flc_lease, "LEASE");
	spin_unlock(&ctx->flc_lock);
}