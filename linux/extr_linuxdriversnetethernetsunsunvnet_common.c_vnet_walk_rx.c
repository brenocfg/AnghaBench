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
typedef  scalar_t__ u32 ;
struct vio_driver_state {int /*<<< orphan*/  _peer_sid; int /*<<< orphan*/  _local_sid; } ;
struct vnet_port {int napi_resume; int napi_stop_idx; struct vio_driver_state vio; } ;
struct vio_dring_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 int ECONNRESET ; 
 int /*<<< orphan*/  VIO_DRING_ACTIVE ; 
 int /*<<< orphan*/  VIO_DRING_STOPPED ; 
 int /*<<< orphan*/  trace_vnet_tx_defer_stopped_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  trace_vnet_tx_send_stopped_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ vio_dring_next (struct vio_dring_state*,scalar_t__) ; 
 scalar_t__ vio_dring_prev (struct vio_dring_state*,scalar_t__) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int vnet_send_ack (struct vnet_port*,struct vio_dring_state*,int,int,int /*<<< orphan*/ ) ; 
 int vnet_walk_rx_one (struct vnet_port*,struct vio_dring_state*,scalar_t__,int*) ; 

__attribute__((used)) static int vnet_walk_rx(struct vnet_port *port, struct vio_dring_state *dr,
			u32 start, u32 end, int *npkts, int budget)
{
	struct vio_driver_state *vio = &port->vio;
	int ack_start = -1, ack_end = -1;
	bool send_ack = true;

	end = (end == (u32)-1) ? vio_dring_prev(dr, start)
			       : vio_dring_next(dr, end);

	viodbg(DATA, "vnet_walk_rx start[%08x] end[%08x]\n", start, end);

	while (start != end) {
		int ack = 0, err = vnet_walk_rx_one(port, dr, start, &ack);

		if (err == -ECONNRESET)
			return err;
		if (err != 0)
			break;
		(*npkts)++;
		if (ack_start == -1)
			ack_start = start;
		ack_end = start;
		start = vio_dring_next(dr, start);
		if (ack && start != end) {
			err = vnet_send_ack(port, dr, ack_start, ack_end,
					    VIO_DRING_ACTIVE);
			if (err == -ECONNRESET)
				return err;
			ack_start = -1;
		}
		if ((*npkts) >= budget) {
			send_ack = false;
			break;
		}
	}
	if (unlikely(ack_start == -1)) {
		ack_end = vio_dring_prev(dr, start);
		ack_start = ack_end;
	}
	if (send_ack) {
		port->napi_resume = false;
		trace_vnet_tx_send_stopped_ack(port->vio._local_sid,
					       port->vio._peer_sid,
					       ack_end, *npkts);
		return vnet_send_ack(port, dr, ack_start, ack_end,
				     VIO_DRING_STOPPED);
	} else  {
		trace_vnet_tx_defer_stopped_ack(port->vio._local_sid,
						port->vio._peer_sid,
						ack_end, *npkts);
		port->napi_resume = true;
		port->napi_stop_idx = ack_end;
		return 1;
	}
}