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
struct xlog {struct xfs_cil* l_cilp; } ;
struct xfs_cil_ctx {int sequence; struct xfs_cil* cil; int /*<<< orphan*/  busy_extents; int /*<<< orphan*/  committing; } ;
struct xfs_cil {int xc_current_sequence; struct xlog* xc_log; struct xfs_cil_ctx* xc_ctx; int /*<<< orphan*/  xc_commit_wait; int /*<<< orphan*/  xc_ctx_lock; int /*<<< orphan*/  xc_push_lock; int /*<<< orphan*/  xc_cil_lock; int /*<<< orphan*/  xc_committing; int /*<<< orphan*/  xc_cil; int /*<<< orphan*/  xc_push_work; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_MAYFAIL ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (struct xfs_cil*) ; 
 void* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xlog_cil_push_work ; 

int
xlog_cil_init(
	struct xlog	*log)
{
	struct xfs_cil	*cil;
	struct xfs_cil_ctx *ctx;

	cil = kmem_zalloc(sizeof(*cil), KM_MAYFAIL);
	if (!cil)
		return -ENOMEM;

	ctx = kmem_zalloc(sizeof(*ctx), KM_MAYFAIL);
	if (!ctx) {
		kmem_free(cil);
		return -ENOMEM;
	}

	INIT_WORK(&cil->xc_push_work, xlog_cil_push_work);
	INIT_LIST_HEAD(&cil->xc_cil);
	INIT_LIST_HEAD(&cil->xc_committing);
	spin_lock_init(&cil->xc_cil_lock);
	spin_lock_init(&cil->xc_push_lock);
	init_rwsem(&cil->xc_ctx_lock);
	init_waitqueue_head(&cil->xc_commit_wait);

	INIT_LIST_HEAD(&ctx->committing);
	INIT_LIST_HEAD(&ctx->busy_extents);
	ctx->sequence = 1;
	ctx->cil = cil;
	cil->xc_ctx = ctx;
	cil->xc_current_sequence = ctx->sequence;

	cil->xc_log = log;
	log->l_cilp = cil;
	return 0;
}