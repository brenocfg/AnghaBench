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
struct svc_rqst {int /*<<< orphan*/  rq_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_DATA ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_xprt_slots_in_range (struct svc_xprt*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool svc_xprt_reserve_slot(struct svc_rqst *rqstp, struct svc_xprt *xprt)
{
	if (!test_bit(RQ_DATA, &rqstp->rq_flags)) {
		if (!svc_xprt_slots_in_range(xprt))
			return false;
		atomic_inc(&xprt->xpt_nr_rqsts);
		set_bit(RQ_DATA, &rqstp->rq_flags);
	}
	return true;
}