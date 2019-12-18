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
struct rdma_cm_id {struct p9_client* context; } ;
struct rdma_cm_event {int event; } ;
struct p9_trans_rdma {int /*<<< orphan*/  cm_done; int /*<<< orphan*/  cm_id; int /*<<< orphan*/  state; } ;
struct p9_client {void* status; struct p9_trans_rdma* trans; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 void* Disconnected ; 
 int /*<<< orphan*/  P9_RDMA_ADDR_RESOLVED ; 
 int /*<<< orphan*/  P9_RDMA_CLOSED ; 
 int /*<<< orphan*/  P9_RDMA_CONNECTED ; 
 int /*<<< orphan*/  P9_RDMA_INIT ; 
 int /*<<< orphan*/  P9_RDMA_ROUTE_RESOLVED ; 
#define  RDMA_CM_EVENT_ADDR_CHANGE 143 
#define  RDMA_CM_EVENT_ADDR_ERROR 142 
#define  RDMA_CM_EVENT_ADDR_RESOLVED 141 
#define  RDMA_CM_EVENT_CONNECT_ERROR 140 
#define  RDMA_CM_EVENT_CONNECT_REQUEST 139 
#define  RDMA_CM_EVENT_CONNECT_RESPONSE 138 
#define  RDMA_CM_EVENT_DEVICE_REMOVAL 137 
#define  RDMA_CM_EVENT_DISCONNECTED 136 
#define  RDMA_CM_EVENT_ESTABLISHED 135 
#define  RDMA_CM_EVENT_MULTICAST_ERROR 134 
#define  RDMA_CM_EVENT_MULTICAST_JOIN 133 
#define  RDMA_CM_EVENT_REJECTED 132 
#define  RDMA_CM_EVENT_ROUTE_ERROR 131 
#define  RDMA_CM_EVENT_ROUTE_RESOLVED 130 
#define  RDMA_CM_EVENT_TIMEWAIT_EXIT 129 
#define  RDMA_CM_EVENT_UNREACHABLE 128 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_disconnect (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
p9_cm_event_handler(struct rdma_cm_id *id, struct rdma_cm_event *event)
{
	struct p9_client *c = id->context;
	struct p9_trans_rdma *rdma = c->trans;
	switch (event->event) {
	case RDMA_CM_EVENT_ADDR_RESOLVED:
		BUG_ON(rdma->state != P9_RDMA_INIT);
		rdma->state = P9_RDMA_ADDR_RESOLVED;
		break;

	case RDMA_CM_EVENT_ROUTE_RESOLVED:
		BUG_ON(rdma->state != P9_RDMA_ADDR_RESOLVED);
		rdma->state = P9_RDMA_ROUTE_RESOLVED;
		break;

	case RDMA_CM_EVENT_ESTABLISHED:
		BUG_ON(rdma->state != P9_RDMA_ROUTE_RESOLVED);
		rdma->state = P9_RDMA_CONNECTED;
		break;

	case RDMA_CM_EVENT_DISCONNECTED:
		if (rdma)
			rdma->state = P9_RDMA_CLOSED;
		c->status = Disconnected;
		break;

	case RDMA_CM_EVENT_TIMEWAIT_EXIT:
		break;

	case RDMA_CM_EVENT_ADDR_CHANGE:
	case RDMA_CM_EVENT_ROUTE_ERROR:
	case RDMA_CM_EVENT_DEVICE_REMOVAL:
	case RDMA_CM_EVENT_MULTICAST_JOIN:
	case RDMA_CM_EVENT_MULTICAST_ERROR:
	case RDMA_CM_EVENT_REJECTED:
	case RDMA_CM_EVENT_CONNECT_REQUEST:
	case RDMA_CM_EVENT_CONNECT_RESPONSE:
	case RDMA_CM_EVENT_CONNECT_ERROR:
	case RDMA_CM_EVENT_ADDR_ERROR:
	case RDMA_CM_EVENT_UNREACHABLE:
		c->status = Disconnected;
		rdma_disconnect(rdma->cm_id);
		break;
	default:
		BUG();
	}
	complete(&rdma->cm_done);
	return 0;
}