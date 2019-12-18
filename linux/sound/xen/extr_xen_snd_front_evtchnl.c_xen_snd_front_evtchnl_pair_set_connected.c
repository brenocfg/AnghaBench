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
struct TYPE_3__ {int state; int /*<<< orphan*/  ring_io_lock; } ;
struct TYPE_4__ {int state; int /*<<< orphan*/  ring_io_lock; } ;
struct xen_snd_front_evtchnl_pair {TYPE_1__ evt; TYPE_2__ req; } ;
typedef  enum xen_snd_front_evtchnl_state { ____Placeholder_xen_snd_front_evtchnl_state } xen_snd_front_evtchnl_state ;

/* Variables and functions */
 int EVTCHNL_STATE_CONNECTED ; 
 int EVTCHNL_STATE_DISCONNECTED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void xen_snd_front_evtchnl_pair_set_connected(struct xen_snd_front_evtchnl_pair *evt_pair,
					      bool is_connected)
{
	enum xen_snd_front_evtchnl_state state;

	if (is_connected)
		state = EVTCHNL_STATE_CONNECTED;
	else
		state = EVTCHNL_STATE_DISCONNECTED;

	mutex_lock(&evt_pair->req.ring_io_lock);
	evt_pair->req.state = state;
	mutex_unlock(&evt_pair->req.ring_io_lock);

	mutex_lock(&evt_pair->evt.ring_io_lock);
	evt_pair->evt.state = state;
	mutex_unlock(&evt_pair->evt.ring_io_lock);
}