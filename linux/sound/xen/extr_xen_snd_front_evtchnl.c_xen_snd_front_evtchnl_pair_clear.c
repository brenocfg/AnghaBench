#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ring_io_lock; scalar_t__ evt_next_id; } ;
struct TYPE_3__ {int /*<<< orphan*/  ring_io_lock; scalar_t__ evt_next_id; } ;
struct xen_snd_front_evtchnl_pair {TYPE_2__ evt; TYPE_1__ req; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void xen_snd_front_evtchnl_pair_clear(struct xen_snd_front_evtchnl_pair *evt_pair)
{
	mutex_lock(&evt_pair->req.ring_io_lock);
	evt_pair->req.evt_next_id = 0;
	mutex_unlock(&evt_pair->req.ring_io_lock);

	mutex_lock(&evt_pair->evt.ring_io_lock);
	evt_pair->evt.evt_next_id = 0;
	mutex_unlock(&evt_pair->evt.ring_io_lock);
}