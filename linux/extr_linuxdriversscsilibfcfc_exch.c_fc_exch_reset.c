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
struct fc_seq {int dummy; } ;
struct fc_exch {int esb_stat; int /*<<< orphan*/  arg; int /*<<< orphan*/  ex_lock; struct fc_seq seq; int /*<<< orphan*/  ex_refcnt; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_PTR (int /*<<< orphan*/ ) ; 
 int ESB_ST_REC_QUAL ; 
 int /*<<< orphan*/  FC_EX_CLOSED ; 
 int /*<<< orphan*/  FC_EX_RST_CLEANUP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_exch_delete (struct fc_exch*) ; 
 int fc_exch_done_locked (struct fc_exch*) ; 
 int /*<<< orphan*/  fc_exch_hold (struct fc_exch*) ; 
 int /*<<< orphan*/  fc_exch_release (struct fc_exch*) ; 
 int /*<<< orphan*/  fc_exch_timer_cancel (struct fc_exch*) ; 
 int /*<<< orphan*/  fc_invoke_resp (struct fc_exch*,struct fc_seq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_seq_set_resp (struct fc_seq*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_exch_reset(struct fc_exch *ep)
{
	struct fc_seq *sp;
	int rc = 1;

	spin_lock_bh(&ep->ex_lock);
	ep->state |= FC_EX_RST_CLEANUP;
	fc_exch_timer_cancel(ep);
	if (ep->esb_stat & ESB_ST_REC_QUAL)
		atomic_dec(&ep->ex_refcnt);	/* drop hold for rec_qual */
	ep->esb_stat &= ~ESB_ST_REC_QUAL;
	sp = &ep->seq;
	rc = fc_exch_done_locked(ep);
	spin_unlock_bh(&ep->ex_lock);

	fc_exch_hold(ep);

	if (!rc)
		fc_exch_delete(ep);

	fc_invoke_resp(ep, sp, ERR_PTR(-FC_EX_CLOSED));
	fc_seq_set_resp(sp, NULL, ep->arg);
	fc_exch_release(ep);
}