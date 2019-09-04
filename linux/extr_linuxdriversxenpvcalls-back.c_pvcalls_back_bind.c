#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  id; } ;
struct TYPE_12__ {TYPE_2__ bind; } ;
struct xen_pvcalls_response {int ret; TYPE_3__ u; int /*<<< orphan*/  cmd; int /*<<< orphan*/  req_id; } ;
struct TYPE_13__ {int /*<<< orphan*/  id; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct TYPE_14__ {TYPE_4__ bind; } ;
struct xen_pvcalls_request {TYPE_5__ u; int /*<<< orphan*/  cmd; int /*<<< orphan*/  req_id; } ;
struct sockpass_mapping {scalar_t__ wq; TYPE_6__* sock; int /*<<< orphan*/  saved_data_ready; int /*<<< orphan*/  id; struct pvcalls_fedata* fedata; int /*<<< orphan*/  copy_lock; int /*<<< orphan*/  register_work; } ;
struct sockaddr {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  rsp_prod_pvt; } ;
struct pvcalls_fedata {TYPE_9__ ring; int /*<<< orphan*/  socket_lock; int /*<<< orphan*/  socketpass_mappings; } ;
struct TYPE_15__ {TYPE_1__* sk; } ;
struct TYPE_10__ {int /*<<< orphan*/  sk_callback_lock; int /*<<< orphan*/  sk_data_ready; struct sockpass_mapping* sk_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct xen_pvcalls_response* RING_GET_RESPONSE (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  WQ_UNBOUND ; 
 int /*<<< orphan*/  __pvcalls_back_accept ; 
 scalar_t__ alloc_workqueue (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 struct pvcalls_fedata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int inet_bind (TYPE_6__*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct sockpass_mapping*) ; 
 struct sockpass_mapping* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvcalls_pass_sk_data_ready ; 
 int radix_tree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sockpass_mapping*) ; 
 int sock_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__**) ; 
 int /*<<< orphan*/  sock_release (TYPE_6__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pvcalls_back_bind(struct xenbus_device *dev,
			     struct xen_pvcalls_request *req)
{
	struct pvcalls_fedata *fedata;
	int ret;
	struct sockpass_mapping *map;
	struct xen_pvcalls_response *rsp;

	fedata = dev_get_drvdata(&dev->dev);

	map = kzalloc(sizeof(*map), GFP_KERNEL);
	if (map == NULL) {
		ret = -ENOMEM;
		goto out;
	}

	INIT_WORK(&map->register_work, __pvcalls_back_accept);
	spin_lock_init(&map->copy_lock);
	map->wq = alloc_workqueue("pvcalls_wq", WQ_UNBOUND, 1);
	if (!map->wq) {
		ret = -ENOMEM;
		goto out;
	}

	ret = sock_create(AF_INET, SOCK_STREAM, 0, &map->sock);
	if (ret < 0)
		goto out;

	ret = inet_bind(map->sock, (struct sockaddr *)&req->u.bind.addr,
			req->u.bind.len);
	if (ret < 0)
		goto out;

	map->fedata = fedata;
	map->id = req->u.bind.id;

	down(&fedata->socket_lock);
	ret = radix_tree_insert(&fedata->socketpass_mappings, map->id,
				map);
	up(&fedata->socket_lock);
	if (ret)
		goto out;

	write_lock_bh(&map->sock->sk->sk_callback_lock);
	map->saved_data_ready = map->sock->sk->sk_data_ready;
	map->sock->sk->sk_user_data = map;
	map->sock->sk->sk_data_ready = pvcalls_pass_sk_data_ready;
	write_unlock_bh(&map->sock->sk->sk_callback_lock);

out:
	if (ret) {
		if (map && map->sock)
			sock_release(map->sock);
		if (map && map->wq)
			destroy_workqueue(map->wq);
		kfree(map);
	}
	rsp = RING_GET_RESPONSE(&fedata->ring, fedata->ring.rsp_prod_pvt++);
	rsp->req_id = req->req_id;
	rsp->cmd = req->cmd;
	rsp->u.bind.id = req->u.bind.id;
	rsp->ret = ret;
	return 0;
}