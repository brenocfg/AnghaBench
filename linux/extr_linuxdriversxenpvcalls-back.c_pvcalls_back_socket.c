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
struct TYPE_7__ {TYPE_1__ socket; } ;
struct xen_pvcalls_response {int ret; TYPE_2__ u; int /*<<< orphan*/  cmd; int /*<<< orphan*/  req_id; } ;
struct TYPE_8__ {scalar_t__ domain; scalar_t__ type; scalar_t__ protocol; int /*<<< orphan*/  id; } ;
struct TYPE_9__ {TYPE_3__ socket; } ;
struct xen_pvcalls_request {TYPE_4__ u; int /*<<< orphan*/  cmd; int /*<<< orphan*/  req_id; } ;
struct TYPE_10__ {int /*<<< orphan*/  rsp_prod_pvt; } ;
struct pvcalls_fedata {TYPE_5__ ring; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int EAFNOSUPPORT ; 
 scalar_t__ IPPROTO_IP ; 
 struct xen_pvcalls_response* RING_GET_RESPONSE (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ SOCK_STREAM ; 
 struct pvcalls_fedata* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pvcalls_back_socket(struct xenbus_device *dev,
		struct xen_pvcalls_request *req)
{
	struct pvcalls_fedata *fedata;
	int ret;
	struct xen_pvcalls_response *rsp;

	fedata = dev_get_drvdata(&dev->dev);

	if (req->u.socket.domain != AF_INET ||
	    req->u.socket.type != SOCK_STREAM ||
	    (req->u.socket.protocol != IPPROTO_IP &&
	     req->u.socket.protocol != AF_INET))
		ret = -EAFNOSUPPORT;
	else
		ret = 0;

	/* leave the actual socket allocation for later */

	rsp = RING_GET_RESPONSE(&fedata->ring, fedata->ring.rsp_prod_pvt++);
	rsp->req_id = req->req_id;
	rsp->cmd = req->cmd;
	rsp->u.socket.id = req->u.socket.id;
	rsp->ret = ret;

	return 0;
}