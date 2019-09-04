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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  indicat_flags; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;
struct htc_packet {scalar_t__ endpoint; TYPE_2__ info; } ;
struct htc_frame_hdr {scalar_t__ eid; } ;
struct htc_endpoint {int /*<<< orphan*/  rx_bufq; } ;

/* Variables and functions */
 int /*<<< orphan*/  HTC_RX_FLAGS_INDICATE_MORE_PKTS ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath6kl_htc_rx_set_indicate(u32 lk_ahd,
				       struct htc_endpoint *endpoint,
				       struct htc_packet *packet)
{
	struct htc_frame_hdr *htc_hdr = (struct htc_frame_hdr *)&lk_ahd;

	if (htc_hdr->eid == packet->endpoint) {
		if (!list_empty(&endpoint->rx_bufq))
			packet->info.rx.indicat_flags |=
					HTC_RX_FLAGS_INDICATE_MORE_PKTS;
	}
}