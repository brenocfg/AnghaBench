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
struct TYPE_3__ {int flags; } ;
struct TYPE_4__ {TYPE_1__ tx; } ;
struct htc_packet {TYPE_2__ info; int /*<<< orphan*/  skb; } ;
struct htc_frame_hdr {int dummy; } ;

/* Variables and functions */
 int HTC_FLAGS_TX_FIXUP_NETBUF ; 
 int /*<<< orphan*/  skb_pull (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void restore_tx_packet(struct htc_packet *packet)
{
	if (packet->info.tx.flags & HTC_FLAGS_TX_FIXUP_NETBUF) {
		skb_pull(packet->skb, sizeof(struct htc_frame_hdr));
		packet->info.tx.flags &= ~HTC_FLAGS_TX_FIXUP_NETBUF;
	}
}