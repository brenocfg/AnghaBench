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
struct svc_xprt {TYPE_1__* xpt_ops; int /*<<< orphan*/  xpt_flags; } ;
struct TYPE_2__ {scalar_t__ (* xpo_has_wspace ) (struct svc_xprt*) ;} ;

/* Variables and functions */
 unsigned long BIT (int /*<<< orphan*/ ) ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XPT_CLOSE ; 
 int /*<<< orphan*/  XPT_CONN ; 
 int /*<<< orphan*/  XPT_DATA ; 
 int /*<<< orphan*/  XPT_DEFERRED ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ stub1 (struct svc_xprt*) ; 
 scalar_t__ svc_xprt_slots_in_range (struct svc_xprt*) ; 
 int /*<<< orphan*/  trace_svc_xprt_no_write_space (struct svc_xprt*) ; 

__attribute__((used)) static bool svc_xprt_ready(struct svc_xprt *xprt)
{
	unsigned long xpt_flags;

	/*
	 * If another cpu has recently updated xpt_flags,
	 * sk_sock->flags, xpt_reserved, or xpt_nr_rqsts, we need to
	 * know about it; otherwise it's possible that both that cpu and
	 * this one could call svc_xprt_enqueue() without either
	 * svc_xprt_enqueue() recognizing that the conditions below
	 * are satisfied, and we could stall indefinitely:
	 */
	smp_rmb();
	xpt_flags = READ_ONCE(xprt->xpt_flags);

	if (xpt_flags & (BIT(XPT_CONN) | BIT(XPT_CLOSE)))
		return true;
	if (xpt_flags & (BIT(XPT_DATA) | BIT(XPT_DEFERRED))) {
		if (xprt->xpt_ops->xpo_has_wspace(xprt) &&
		    svc_xprt_slots_in_range(xprt))
			return true;
		trace_svc_xprt_no_write_space(xprt);
		return false;
	}
	return false;
}