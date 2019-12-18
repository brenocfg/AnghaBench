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
struct TYPE_6__ {int /*<<< orphan*/  req_prod_pvt; } ;
struct TYPE_4__ {TYPE_3__ ring; } ;
struct TYPE_5__ {TYPE_1__ req; } ;
struct xen_snd_front_evtchnl {int /*<<< orphan*/  irq; TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  RING_PUSH_REQUESTS_AND_CHECK_NOTIFY (TYPE_3__*,int) ; 
 int /*<<< orphan*/  notify_remote_via_irq (int /*<<< orphan*/ ) ; 

void xen_snd_front_evtchnl_flush(struct xen_snd_front_evtchnl *channel)
{
	int notify;

	channel->u.req.ring.req_prod_pvt++;
	RING_PUSH_REQUESTS_AND_CHECK_NOTIFY(&channel->u.req.ring, notify);
	if (notify)
		notify_remote_via_irq(channel->irq);
}