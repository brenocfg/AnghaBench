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
struct TYPE_4__ {int sb_status; } ;
struct ocfs2_dlm_lksb {TYPE_3__* lksb_conn; TYPE_1__ lksb_fsdlm; } ;
struct TYPE_6__ {TYPE_2__* cc_proto; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* lp_lock_ast ) (struct ocfs2_dlm_lksb*) ;int /*<<< orphan*/  (* lp_unlock_ast ) (struct ocfs2_dlm_lksb*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int DLM_ECANCEL ; 
 int DLM_EUNLOCK ; 
 int /*<<< orphan*/  stub1 (struct ocfs2_dlm_lksb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ocfs2_dlm_lksb*) ; 

__attribute__((used)) static void fsdlm_lock_ast_wrapper(void *astarg)
{
	struct ocfs2_dlm_lksb *lksb = astarg;
	int status = lksb->lksb_fsdlm.sb_status;

	/*
	 * For now we're punting on the issue of other non-standard errors
	 * where we can't tell if the unlock_ast or lock_ast should be called.
	 * The main "other error" that's possible is EINVAL which means the
	 * function was called with invalid args, which shouldn't be possible
	 * since the caller here is under our control.  Other non-standard
	 * errors probably fall into the same category, or otherwise are fatal
	 * which means we can't carry on anyway.
	 */

	if (status == -DLM_EUNLOCK || status == -DLM_ECANCEL)
		lksb->lksb_conn->cc_proto->lp_unlock_ast(lksb, 0);
	else
		lksb->lksb_conn->cc_proto->lp_lock_ast(lksb);
}