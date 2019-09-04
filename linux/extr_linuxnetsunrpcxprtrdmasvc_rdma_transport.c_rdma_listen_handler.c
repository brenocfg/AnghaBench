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
struct sockaddr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  src_addr; } ;
struct TYPE_6__ {TYPE_2__ addr; } ;
struct rdma_cm_id {int /*<<< orphan*/  context; TYPE_3__ route; } ;
struct TYPE_4__ {int /*<<< orphan*/  conn; } ;
struct rdma_cm_event {int event; TYPE_1__ param; } ;

/* Variables and functions */
#define  RDMA_CM_EVENT_CONNECT_REQUEST 128 
 int /*<<< orphan*/  dprintk (char*,struct rdma_cm_id*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  handle_connect_req (struct rdma_cm_id*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_event_msg (int) ; 
 int /*<<< orphan*/  trace_svcrdma_cm_event (struct rdma_cm_event*,struct sockaddr*) ; 

__attribute__((used)) static int rdma_listen_handler(struct rdma_cm_id *cma_id,
			       struct rdma_cm_event *event)
{
	struct sockaddr *sap = (struct sockaddr *)&cma_id->route.addr.src_addr;

	trace_svcrdma_cm_event(event, sap);

	switch (event->event) {
	case RDMA_CM_EVENT_CONNECT_REQUEST:
		dprintk("svcrdma: Connect request on cma_id=%p, xprt = %p, "
			"event = %s (%d)\n", cma_id, cma_id->context,
			rdma_event_msg(event->event), event->event);
		handle_connect_req(cma_id, &event->param.conn);
		break;
	default:
		/* NB: No device removal upcall for INADDR_ANY listeners */
		dprintk("svcrdma: Unexpected event on listening endpoint %p, "
			"event = %s (%d)\n", cma_id,
			rdma_event_msg(event->event), event->event);
		break;
	}

	return 0;
}