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
struct svc_xprt {int /*<<< orphan*/  xpt_nr_rqsts; } ;
struct svc_rqst {int /*<<< orphan*/  rq_flags; struct svc_xprt* rq_xprt; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_DATA ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  svc_xprt_enqueue (struct svc_xprt*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void svc_xprt_release_slot(struct svc_rqst *rqstp)
{
	struct svc_xprt	*xprt = rqstp->rq_xprt;
	if (test_and_clear_bit(RQ_DATA, &rqstp->rq_flags)) {
		atomic_dec(&xprt->xpt_nr_rqsts);
		smp_wmb(); /* See smp_rmb() in svc_xprt_ready() */
		svc_xprt_enqueue(xprt);
	}
}