#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {uintptr_t id; int /*<<< orphan*/  protocol; scalar_t__ type; int /*<<< orphan*/  domain; } ;
struct TYPE_10__ {TYPE_2__ socket; } ;
struct xen_pvcalls_request {int req_id; TYPE_3__ u; int /*<<< orphan*/  cmd; } ;
struct socket {scalar_t__ type; TYPE_1__* sk; } ;
struct sock_mapping {int /*<<< orphan*/  list; } ;
struct TYPE_13__ {int /*<<< orphan*/  req_prod_pvt; } ;
struct pvcalls_bedata {TYPE_4__* rsp; int /*<<< orphan*/  inflight_req; int /*<<< orphan*/  irq; int /*<<< orphan*/  socket_lock; TYPE_6__ ring; int /*<<< orphan*/  socket_mappings; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {int ret; int /*<<< orphan*/  req_id; } ;
struct TYPE_8__ {void* sk_send_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EACCES ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  PVCALLS_INVALID_ID ; 
 int /*<<< orphan*/  PVCALLS_SOCKET ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 struct xen_pvcalls_request* RING_GET_REQUEST (TYPE_6__*,int) ; 
 int /*<<< orphan*/  RING_PUSH_REQUESTS_AND_CHECK_NOTIFY (TYPE_6__*,int) ; 
 scalar_t__ SOCK_STREAM ; 
 struct pvcalls_bedata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int get_request (struct pvcalls_bedata*,int*) ; 
 int /*<<< orphan*/  kfree (struct sock_mapping*) ; 
 struct sock_mapping* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvcalls_enter () ; 
 int /*<<< orphan*/  pvcalls_exit () ; 
 TYPE_5__* pvcalls_front_dev ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int pvcalls_front_socket(struct socket *sock)
{
	struct pvcalls_bedata *bedata;
	struct sock_mapping *map = NULL;
	struct xen_pvcalls_request *req;
	int notify, req_id, ret;

	/*
	 * PVCalls only supports domain AF_INET,
	 * type SOCK_STREAM and protocol 0 sockets for now.
	 *
	 * Check socket type here, AF_INET and protocol checks are done
	 * by the caller.
	 */
	if (sock->type != SOCK_STREAM)
		return -EOPNOTSUPP;

	pvcalls_enter();
	if (!pvcalls_front_dev) {
		pvcalls_exit();
		return -EACCES;
	}
	bedata = dev_get_drvdata(&pvcalls_front_dev->dev);

	map = kzalloc(sizeof(*map), GFP_KERNEL);
	if (map == NULL) {
		pvcalls_exit();
		return -ENOMEM;
	}

	spin_lock(&bedata->socket_lock);

	ret = get_request(bedata, &req_id);
	if (ret < 0) {
		kfree(map);
		spin_unlock(&bedata->socket_lock);
		pvcalls_exit();
		return ret;
	}

	/*
	 * sock->sk->sk_send_head is not used for ip sockets: reuse the
	 * field to store a pointer to the struct sock_mapping
	 * corresponding to the socket. This way, we can easily get the
	 * struct sock_mapping from the struct socket.
	 */
	sock->sk->sk_send_head = (void *)map;
	list_add_tail(&map->list, &bedata->socket_mappings);

	req = RING_GET_REQUEST(&bedata->ring, req_id);
	req->req_id = req_id;
	req->cmd = PVCALLS_SOCKET;
	req->u.socket.id = (uintptr_t) map;
	req->u.socket.domain = AF_INET;
	req->u.socket.type = SOCK_STREAM;
	req->u.socket.protocol = IPPROTO_IP;

	bedata->ring.req_prod_pvt++;
	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&bedata->ring, notify);
	spin_unlock(&bedata->socket_lock);
	if (notify)
		notify_remote_via_irq(bedata->irq);

	wait_event(bedata->inflight_req,
		   READ_ONCE(bedata->rsp[req_id].req_id) == req_id);

	/* read req_id, then the content */
	smp_rmb();
	ret = bedata->rsp[req_id].ret;
	bedata->rsp[req_id].req_id = PVCALLS_INVALID_ID;

	pvcalls_exit();
	return ret;
}