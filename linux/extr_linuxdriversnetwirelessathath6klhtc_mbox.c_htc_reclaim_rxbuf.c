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
struct htc_target {int dummy; } ;
struct TYPE_4__ {int rx_flags; } ;
struct TYPE_5__ {TYPE_1__ rx; } ;
struct htc_packet {int /*<<< orphan*/  status; TYPE_2__ info; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* rx ) (int /*<<< orphan*/ ,struct htc_packet*) ;} ;
struct htc_endpoint {int /*<<< orphan*/  target; TYPE_3__ ep_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECANCELED ; 
 int HTC_RX_PKT_NO_RECYCLE ; 
 int /*<<< orphan*/  htc_add_rxbuf (void*,struct htc_packet*) ; 
 int /*<<< orphan*/  htc_rxpkt_reset (struct htc_packet*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct htc_packet*) ; 

__attribute__((used)) static void htc_reclaim_rxbuf(struct htc_target *target,
			      struct htc_packet *packet,
			      struct htc_endpoint *ep)
{
	if (packet->info.rx.rx_flags & HTC_RX_PKT_NO_RECYCLE) {
		htc_rxpkt_reset(packet);
		packet->status = -ECANCELED;
		ep->ep_cb.rx(ep->target, packet);
	} else {
		htc_rxpkt_reset(packet);
		htc_add_rxbuf((void *)(target), packet);
	}
}