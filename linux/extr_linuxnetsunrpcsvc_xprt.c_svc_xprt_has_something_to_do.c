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
struct svc_xprt {int xpt_flags; TYPE_1__* xpt_ops; } ;
struct TYPE_2__ {scalar_t__ (* xpo_has_wspace ) (struct svc_xprt*) ;} ;

/* Variables and functions */
 int XPT_CLOSE ; 
 int XPT_CONN ; 
 int XPT_DATA ; 
 int XPT_DEFERRED ; 
 scalar_t__ stub1 (struct svc_xprt*) ; 
 scalar_t__ svc_xprt_slots_in_range (struct svc_xprt*) ; 
 int /*<<< orphan*/  trace_svc_xprt_no_write_space (struct svc_xprt*) ; 

__attribute__((used)) static bool svc_xprt_has_something_to_do(struct svc_xprt *xprt)
{
	if (xprt->xpt_flags & ((1<<XPT_CONN)|(1<<XPT_CLOSE)))
		return true;
	if (xprt->xpt_flags & ((1<<XPT_DATA)|(1<<XPT_DEFERRED))) {
		if (xprt->xpt_ops->xpo_has_wspace(xprt) &&
		    svc_xprt_slots_in_range(xprt))
			return true;
		trace_svc_xprt_no_write_space(xprt);
		return false;
	}
	return false;
}