#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vio_driver_state {struct vio_dring_state* drings; } ;
struct vnet_port {int /*<<< orphan*/  napi_resume; struct vio_driver_state vio; } ;
struct vio_dring_state {scalar_t__ rcv_nxt; } ;
struct TYPE_2__ {scalar_t__ stype_env; } ;
struct vio_dring_data {scalar_t__ seq; int /*<<< orphan*/  end_idx; int /*<<< orphan*/  start_idx; TYPE_1__ tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA ; 
 scalar_t__ VIO_DRING_DATA ; 
 size_t VIO_DRIVER_RX_RING ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  viodbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int vnet_walk_rx (struct vnet_port*,struct vio_dring_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int vnet_rx(struct vnet_port *port, void *msgbuf, int *npkts,
		   int budget)
{
	struct vio_dring_data *pkt = msgbuf;
	struct vio_dring_state *dr = &port->vio.drings[VIO_DRIVER_RX_RING];
	struct vio_driver_state *vio = &port->vio;

	viodbg(DATA, "vnet_rx stype_env[%04x] seq[%016llx] rcv_nxt[%016llx]\n",
	       pkt->tag.stype_env, pkt->seq, dr->rcv_nxt);

	if (unlikely(pkt->tag.stype_env != VIO_DRING_DATA))
		return 0;
	if (unlikely(pkt->seq != dr->rcv_nxt)) {
		pr_err("RX out of sequence seq[0x%llx] rcv_nxt[0x%llx]\n",
		       pkt->seq, dr->rcv_nxt);
		return 0;
	}

	if (!port->napi_resume)
		dr->rcv_nxt++;

	/* XXX Validate pkt->start_idx and pkt->end_idx XXX */

	return vnet_walk_rx(port, dr, pkt->start_idx, pkt->end_idx,
			    npkts, budget);
}