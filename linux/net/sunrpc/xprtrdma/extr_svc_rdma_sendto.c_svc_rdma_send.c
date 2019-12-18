#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  xpt_flags; } ;
struct svcxprt_rdma {int /*<<< orphan*/  sc_send_wait; TYPE_1__ sc_xprt; int /*<<< orphan*/  sc_qp; int /*<<< orphan*/  sc_sq_avail; } ;
struct ib_send_wr {int dummy; } ;

/* Variables and functions */
 int ENOTCONN ; 
 int /*<<< orphan*/  XPT_CLOSE ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int ib_post_send (int /*<<< orphan*/ ,struct ib_send_wr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  rdma_stat_sq_starve ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_xprt_get (TYPE_1__*) ; 
 int /*<<< orphan*/  svc_xprt_put (TYPE_1__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_svcrdma_post_send (struct ib_send_wr*,int) ; 
 int /*<<< orphan*/  trace_svcrdma_sq_full (struct svcxprt_rdma*) ; 
 int /*<<< orphan*/  trace_svcrdma_sq_retry (struct svcxprt_rdma*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int svc_rdma_send(struct svcxprt_rdma *rdma, struct ib_send_wr *wr)
{
	int ret;

	might_sleep();

	/* If the SQ is full, wait until an SQ entry is available */
	while (1) {
		if ((atomic_dec_return(&rdma->sc_sq_avail) < 0)) {
			atomic_inc(&rdma_stat_sq_starve);
			trace_svcrdma_sq_full(rdma);
			atomic_inc(&rdma->sc_sq_avail);
			wait_event(rdma->sc_send_wait,
				   atomic_read(&rdma->sc_sq_avail) > 1);
			if (test_bit(XPT_CLOSE, &rdma->sc_xprt.xpt_flags))
				return -ENOTCONN;
			trace_svcrdma_sq_retry(rdma);
			continue;
		}

		svc_xprt_get(&rdma->sc_xprt);
		ret = ib_post_send(rdma->sc_qp, wr, NULL);
		trace_svcrdma_post_send(wr, ret);
		if (ret) {
			set_bit(XPT_CLOSE, &rdma->sc_xprt.xpt_flags);
			svc_xprt_put(&rdma->sc_xprt);
			wake_up(&rdma->sc_send_wait);
		}
		break;
	}
	return ret;
}