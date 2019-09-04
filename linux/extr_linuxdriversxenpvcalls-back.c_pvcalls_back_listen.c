#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct xenbus_device {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_7__ {TYPE_1__ listen; } ;
struct xen_pvcalls_response {int ret; TYPE_2__ u; int /*<<< orphan*/  cmd; int /*<<< orphan*/  req_id; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; int /*<<< orphan*/  backlog; } ;
struct TYPE_9__ {TYPE_3__ listen; } ;
struct xen_pvcalls_request {TYPE_4__ u; int /*<<< orphan*/  cmd; int /*<<< orphan*/  req_id; } ;
struct sockpass_mapping {int /*<<< orphan*/  sock; } ;
struct TYPE_10__ {int /*<<< orphan*/  rsp_prod_pvt; } ;
struct pvcalls_fedata {TYPE_5__ ring; int /*<<< orphan*/  socket_lock; int /*<<< orphan*/  socketpass_mappings; } ;

/* Variables and functions */
 int EINVAL ; 
 struct xen_pvcalls_response* RING_GET_RESPONSE (TYPE_5__*,int /*<<< orphan*/ ) ; 
 struct pvcalls_fedata* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int inet_listen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sockpass_mapping* radix_tree_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pvcalls_back_listen(struct xenbus_device *dev,
			       struct xen_pvcalls_request *req)
{
	struct pvcalls_fedata *fedata;
	int ret = -EINVAL;
	struct sockpass_mapping *map;
	struct xen_pvcalls_response *rsp;

	fedata = dev_get_drvdata(&dev->dev);

	down(&fedata->socket_lock);
	map = radix_tree_lookup(&fedata->socketpass_mappings, req->u.listen.id);
	up(&fedata->socket_lock);
	if (map == NULL)
		goto out;

	ret = inet_listen(map->sock, req->u.listen.backlog);

out:
	rsp = RING_GET_RESPONSE(&fedata->ring, fedata->ring.rsp_prod_pvt++);
	rsp->req_id = req->req_id;
	rsp->cmd = req->cmd;
	rsp->u.listen.id = req->u.listen.id;
	rsp->ret = ret;
	return 0;
}