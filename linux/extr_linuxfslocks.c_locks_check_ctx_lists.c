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
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; struct file_lock_context* i_flctx; } ;
struct file_lock_context {int /*<<< orphan*/  flc_lease; int /*<<< orphan*/  flc_posix; int /*<<< orphan*/  flc_flock; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locks_dump_ctx_list (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
locks_check_ctx_lists(struct inode *inode)
{
	struct file_lock_context *ctx = inode->i_flctx;

	if (unlikely(!list_empty(&ctx->flc_flock) ||
		     !list_empty(&ctx->flc_posix) ||
		     !list_empty(&ctx->flc_lease))) {
		pr_warn("Leaked locks on dev=0x%x:0x%x ino=0x%lx:\n",
			MAJOR(inode->i_sb->s_dev), MINOR(inode->i_sb->s_dev),
			inode->i_ino);
		locks_dump_ctx_list(&ctx->flc_flock, "FLOCK");
		locks_dump_ctx_list(&ctx->flc_posix, "POSIX");
		locks_dump_ctx_list(&ctx->flc_lease, "LEASE");
	}
}