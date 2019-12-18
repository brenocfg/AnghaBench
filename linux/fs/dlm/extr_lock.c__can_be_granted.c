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
struct dlm_rsb {int /*<<< orphan*/  res_waitqueue; int /*<<< orphan*/  res_convertqueue; int /*<<< orphan*/  res_grantqueue; } ;
struct dlm_lkb {scalar_t__ lkb_grmode; int lkb_exflags; } ;
typedef  int int8_t ;

/* Variables and functions */
 int DLM_LKF_EXPEDITE ; 
 int DLM_LKF_NOORDER ; 
 int DLM_LKF_QUECVT ; 
 scalar_t__ DLM_LOCK_IV ; 
 scalar_t__ first_in_list (struct dlm_lkb*,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ queue_conflict (int /*<<< orphan*/ *,struct dlm_lkb*) ; 

__attribute__((used)) static int _can_be_granted(struct dlm_rsb *r, struct dlm_lkb *lkb, int now,
			   int recover)
{
	int8_t conv = (lkb->lkb_grmode != DLM_LOCK_IV);

	/*
	 * 6-10: Version 5.4 introduced an option to address the phenomenon of
	 * a new request for a NL mode lock being blocked.
	 *
	 * 6-11: If the optional EXPEDITE flag is used with the new NL mode
	 * request, then it would be granted.  In essence, the use of this flag
	 * tells the Lock Manager to expedite theis request by not considering
	 * what may be in the CONVERTING or WAITING queues...  As of this
	 * writing, the EXPEDITE flag can be used only with new requests for NL
	 * mode locks.  This flag is not valid for conversion requests.
	 *
	 * A shortcut.  Earlier checks return an error if EXPEDITE is used in a
	 * conversion or used with a non-NL requested mode.  We also know an
	 * EXPEDITE request is always granted immediately, so now must always
	 * be 1.  The full condition to grant an expedite request: (now &&
	 * !conv && lkb->rqmode == DLM_LOCK_NL && (flags & EXPEDITE)) can
	 * therefore be shortened to just checking the flag.
	 */

	if (lkb->lkb_exflags & DLM_LKF_EXPEDITE)
		return 1;

	/*
	 * A shortcut. Without this, !queue_conflict(grantqueue, lkb) would be
	 * added to the remaining conditions.
	 */

	if (queue_conflict(&r->res_grantqueue, lkb))
		return 0;

	/*
	 * 6-3: By default, a conversion request is immediately granted if the
	 * requested mode is compatible with the modes of all other granted
	 * locks
	 */

	if (queue_conflict(&r->res_convertqueue, lkb))
		return 0;

	/*
	 * The RECOVER_GRANT flag means dlm_recover_grant() is granting
	 * locks for a recovered rsb, on which lkb's have been rebuilt.
	 * The lkb's may have been rebuilt on the queues in a different
	 * order than they were in on the previous master.  So, granting
	 * queued conversions in order after recovery doesn't make sense
	 * since the order hasn't been preserved anyway.  The new order
	 * could also have created a new "in place" conversion deadlock.
	 * (e.g. old, failed master held granted EX, with PR->EX, NL->EX.
	 * After recovery, there would be no granted locks, and possibly
	 * NL->EX, PR->EX, an in-place conversion deadlock.)  So, after
	 * recovery, grant conversions without considering order.
	 */

	if (conv && recover)
		return 1;

	/*
	 * 6-5: But the default algorithm for deciding whether to grant or
	 * queue conversion requests does not by itself guarantee that such
	 * requests are serviced on a "first come first serve" basis.  This, in
	 * turn, can lead to a phenomenon known as "indefinate postponement".
	 *
	 * 6-7: This issue is dealt with by using the optional QUECVT flag with
	 * the system service employed to request a lock conversion.  This flag
	 * forces certain conversion requests to be queued, even if they are
	 * compatible with the granted modes of other locks on the same
	 * resource.  Thus, the use of this flag results in conversion requests
	 * being ordered on a "first come first servce" basis.
	 *
	 * DCT: This condition is all about new conversions being able to occur
	 * "in place" while the lock remains on the granted queue (assuming
	 * nothing else conflicts.)  IOW if QUECVT isn't set, a conversion
	 * doesn't _have_ to go onto the convert queue where it's processed in
	 * order.  The "now" variable is necessary to distinguish converts
	 * being received and processed for the first time now, because once a
	 * convert is moved to the conversion queue the condition below applies
	 * requiring fifo granting.
	 */

	if (now && conv && !(lkb->lkb_exflags & DLM_LKF_QUECVT))
		return 1;

	/*
	 * Even if the convert is compat with all granted locks,
	 * QUECVT forces it behind other locks on the convert queue.
	 */

	if (now && conv && (lkb->lkb_exflags & DLM_LKF_QUECVT)) {
		if (list_empty(&r->res_convertqueue))
			return 1;
		else
			return 0;
	}

	/*
	 * The NOORDER flag is set to avoid the standard vms rules on grant
	 * order.
	 */

	if (lkb->lkb_exflags & DLM_LKF_NOORDER)
		return 1;

	/*
	 * 6-3: Once in that queue [CONVERTING], a conversion request cannot be
	 * granted until all other conversion requests ahead of it are granted
	 * and/or canceled.
	 */

	if (!now && conv && first_in_list(lkb, &r->res_convertqueue))
		return 1;

	/*
	 * 6-4: By default, a new request is immediately granted only if all
	 * three of the following conditions are satisfied when the request is
	 * issued:
	 * - The queue of ungranted conversion requests for the resource is
	 *   empty.
	 * - The queue of ungranted new requests for the resource is empty.
	 * - The mode of the new request is compatible with the most
	 *   restrictive mode of all granted locks on the resource.
	 */

	if (now && !conv && list_empty(&r->res_convertqueue) &&
	    list_empty(&r->res_waitqueue))
		return 1;

	/*
	 * 6-4: Once a lock request is in the queue of ungranted new requests,
	 * it cannot be granted until the queue of ungranted conversion
	 * requests is empty, all ungranted new requests ahead of it are
	 * granted and/or canceled, and it is compatible with the granted mode
	 * of the most restrictive lock granted on the resource.
	 */

	if (!now && !conv && list_empty(&r->res_convertqueue) &&
	    first_in_list(lkb, &r->res_waitqueue))
		return 1;

	return 0;
}