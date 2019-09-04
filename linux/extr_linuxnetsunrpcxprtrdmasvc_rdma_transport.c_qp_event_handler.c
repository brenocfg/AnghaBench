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
struct svc_xprt {int /*<<< orphan*/  xpt_flags; int /*<<< orphan*/  xpt_remote; } ;
struct sockaddr {int dummy; } ;
struct ib_event {int event; } ;

/* Variables and functions */
#define  IB_EVENT_COMM_EST 136 
#define  IB_EVENT_DEVICE_FATAL 135 
#define  IB_EVENT_PATH_MIG 134 
#define  IB_EVENT_PATH_MIG_ERR 133 
#define  IB_EVENT_QP_ACCESS_ERR 132 
#define  IB_EVENT_QP_FATAL 131 
#define  IB_EVENT_QP_LAST_WQE_REACHED 130 
#define  IB_EVENT_QP_REQ_ERR 129 
#define  IB_EVENT_SQ_DRAINED 128 
 int /*<<< orphan*/  XPT_CLOSE ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_xprt_enqueue (struct svc_xprt*) ; 
 int /*<<< orphan*/  trace_svcrdma_qp_error (struct ib_event*,struct sockaddr*) ; 

__attribute__((used)) static void qp_event_handler(struct ib_event *event, void *context)
{
	struct svc_xprt *xprt = context;

	trace_svcrdma_qp_error(event, (struct sockaddr *)&xprt->xpt_remote);
	switch (event->event) {
	/* These are considered benign events */
	case IB_EVENT_PATH_MIG:
	case IB_EVENT_COMM_EST:
	case IB_EVENT_SQ_DRAINED:
	case IB_EVENT_QP_LAST_WQE_REACHED:
		break;

	/* These are considered fatal events */
	case IB_EVENT_PATH_MIG_ERR:
	case IB_EVENT_QP_FATAL:
	case IB_EVENT_QP_REQ_ERR:
	case IB_EVENT_QP_ACCESS_ERR:
	case IB_EVENT_DEVICE_FATAL:
	default:
		set_bit(XPT_CLOSE, &xprt->xpt_flags);
		svc_xprt_enqueue(xprt);
		break;
	}
}