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
struct smbd_connection {int /*<<< orphan*/  wait_send_queue; int /*<<< orphan*/  wait_reassembly_queue; int /*<<< orphan*/  disconn_wait; void* transport_status; int /*<<< orphan*/  conn_wait; int /*<<< orphan*/  ri_done; int /*<<< orphan*/  ri_rc; } ;
struct rdma_cm_id {struct smbd_connection* context; } ;
struct rdma_cm_event {int event; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHOSTUNREACH ; 
 int /*<<< orphan*/  ENETUNREACH ; 
 int /*<<< orphan*/  INFO ; 
#define  RDMA_CM_EVENT_ADDR_ERROR 137 
#define  RDMA_CM_EVENT_ADDR_RESOLVED 136 
#define  RDMA_CM_EVENT_CONNECT_ERROR 135 
#define  RDMA_CM_EVENT_DEVICE_REMOVAL 134 
#define  RDMA_CM_EVENT_DISCONNECTED 133 
#define  RDMA_CM_EVENT_ESTABLISHED 132 
#define  RDMA_CM_EVENT_REJECTED 131 
#define  RDMA_CM_EVENT_ROUTE_ERROR 130 
#define  RDMA_CM_EVENT_ROUTE_RESOLVED 129 
#define  RDMA_CM_EVENT_UNREACHABLE 128 
 void* SMBD_CONNECTED ; 
 void* SMBD_DISCONNECTED ; 
 void* SMBD_NEGOTIATE_FAILED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_rdma_event (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smbd_conn_upcall(
		struct rdma_cm_id *id, struct rdma_cm_event *event)
{
	struct smbd_connection *info = id->context;

	log_rdma_event(INFO, "event=%d status=%d\n",
		event->event, event->status);

	switch (event->event) {
	case RDMA_CM_EVENT_ADDR_RESOLVED:
	case RDMA_CM_EVENT_ROUTE_RESOLVED:
		info->ri_rc = 0;
		complete(&info->ri_done);
		break;

	case RDMA_CM_EVENT_ADDR_ERROR:
		info->ri_rc = -EHOSTUNREACH;
		complete(&info->ri_done);
		break;

	case RDMA_CM_EVENT_ROUTE_ERROR:
		info->ri_rc = -ENETUNREACH;
		complete(&info->ri_done);
		break;

	case RDMA_CM_EVENT_ESTABLISHED:
		log_rdma_event(INFO, "connected event=%d\n", event->event);
		info->transport_status = SMBD_CONNECTED;
		wake_up_interruptible(&info->conn_wait);
		break;

	case RDMA_CM_EVENT_CONNECT_ERROR:
	case RDMA_CM_EVENT_UNREACHABLE:
	case RDMA_CM_EVENT_REJECTED:
		log_rdma_event(INFO, "connecting failed event=%d\n", event->event);
		info->transport_status = SMBD_DISCONNECTED;
		wake_up_interruptible(&info->conn_wait);
		break;

	case RDMA_CM_EVENT_DEVICE_REMOVAL:
	case RDMA_CM_EVENT_DISCONNECTED:
		/* This happenes when we fail the negotiation */
		if (info->transport_status == SMBD_NEGOTIATE_FAILED) {
			info->transport_status = SMBD_DISCONNECTED;
			wake_up(&info->conn_wait);
			break;
		}

		info->transport_status = SMBD_DISCONNECTED;
		wake_up_interruptible(&info->disconn_wait);
		wake_up_interruptible(&info->wait_reassembly_queue);
		wake_up_interruptible_all(&info->wait_send_queue);
		break;

	default:
		break;
	}

	return 0;
}