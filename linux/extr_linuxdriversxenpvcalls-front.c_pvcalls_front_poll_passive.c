#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_9__ {uintptr_t id; } ;
struct TYPE_10__ {TYPE_3__ poll; } ;
struct xen_pvcalls_request {int req_id; TYPE_4__ u; int /*<<< orphan*/  cmd; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  inflight_accept_req; int /*<<< orphan*/  inflight_req_id; } ;
struct sock_mapping {TYPE_2__ passive; } ;
struct TYPE_11__ {int /*<<< orphan*/  req_prod_pvt; } ;
struct pvcalls_bedata {int /*<<< orphan*/  inflight_req; int /*<<< orphan*/  irq; int /*<<< orphan*/  socket_lock; TYPE_5__ ring; TYPE_1__* rsp; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_7__ {int /*<<< orphan*/  req_id; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLRDNORM ; 
 int /*<<< orphan*/  PVCALLS_FLAG_ACCEPT_INFLIGHT ; 
 int /*<<< orphan*/  PVCALLS_FLAG_POLL_INFLIGHT ; 
 int /*<<< orphan*/  PVCALLS_FLAG_POLL_RET ; 
 size_t PVCALLS_INVALID_ID ; 
 int /*<<< orphan*/  PVCALLS_POLL ; 
 size_t READ_ONCE (int /*<<< orphan*/ ) ; 
 struct xen_pvcalls_request* RING_GET_REQUEST (TYPE_5__*,int) ; 
 int /*<<< orphan*/  RING_PUSH_REQUESTS_AND_CHECK_NOTIFY (TYPE_5__*,int) ; 
 int get_request (struct pvcalls_bedata*,int*) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static __poll_t pvcalls_front_poll_passive(struct file *file,
					       struct pvcalls_bedata *bedata,
					       struct sock_mapping *map,
					       poll_table *wait)
{
	int notify, req_id, ret;
	struct xen_pvcalls_request *req;

	if (test_bit(PVCALLS_FLAG_ACCEPT_INFLIGHT,
		     (void *)&map->passive.flags)) {
		uint32_t req_id = READ_ONCE(map->passive.inflight_req_id);

		if (req_id != PVCALLS_INVALID_ID &&
		    READ_ONCE(bedata->rsp[req_id].req_id) == req_id)
			return EPOLLIN | EPOLLRDNORM;

		poll_wait(file, &map->passive.inflight_accept_req, wait);
		return 0;
	}

	if (test_and_clear_bit(PVCALLS_FLAG_POLL_RET,
			       (void *)&map->passive.flags))
		return EPOLLIN | EPOLLRDNORM;

	/*
	 * First check RET, then INFLIGHT. No barriers necessary to
	 * ensure execution ordering because of the conditional
	 * instructions creating control dependencies.
	 */

	if (test_and_set_bit(PVCALLS_FLAG_POLL_INFLIGHT,
			     (void *)&map->passive.flags)) {
		poll_wait(file, &bedata->inflight_req, wait);
		return 0;
	}

	spin_lock(&bedata->socket_lock);
	ret = get_request(bedata, &req_id);
	if (ret < 0) {
		spin_unlock(&bedata->socket_lock);
		return ret;
	}
	req = RING_GET_REQUEST(&bedata->ring, req_id);
	req->req_id = req_id;
	req->cmd = PVCALLS_POLL;
	req->u.poll.id = (uintptr_t) map;

	bedata->ring.req_prod_pvt++;
	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&bedata->ring, notify);
	spin_unlock(&bedata->socket_lock);
	if (notify)
		notify_remote_via_irq(bedata->irq);

	poll_wait(file, &bedata->inflight_req, wait);
	return 0;
}