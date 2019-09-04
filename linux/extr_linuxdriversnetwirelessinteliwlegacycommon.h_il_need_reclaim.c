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
struct TYPE_2__ {int sequence; scalar_t__ cmd; } ;
struct il_rx_pkt {TYPE_1__ hdr; } ;
struct il_priv {int dummy; } ;

/* Variables and functions */
 scalar_t__ C_TX ; 
 scalar_t__ N_COMPRESSED_BA ; 
 scalar_t__ N_RX ; 
 scalar_t__ N_RX_MPDU ; 
 scalar_t__ N_RX_PHY ; 
 scalar_t__ N_STATS ; 
 int SEQ_RX_FRAME ; 

__attribute__((used)) static inline bool il_need_reclaim(struct il_priv *il, struct il_rx_pkt *pkt)
{
	/* Reclaim a command buffer only if this packet is a response
	 * to a (driver-originated) command. If the packet (e.g. Rx frame)
	 * originated from uCode, there is no command buffer to reclaim.
	 * Ucode should set SEQ_RX_FRAME bit if ucode-originated, but
	 * apparently a few don't get set; catch them here.
	 */
	return !(pkt->hdr.sequence & SEQ_RX_FRAME) &&
	       pkt->hdr.cmd != N_STATS && pkt->hdr.cmd != C_TX &&
	       pkt->hdr.cmd != N_RX_PHY && pkt->hdr.cmd != N_RX &&
	       pkt->hdr.cmd != N_RX_MPDU && pkt->hdr.cmd != N_COMPRESSED_BA;
}