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
struct netcp_packet {int /*<<< orphan*/ * tx_pipe; } ;
struct gbe_intf {int /*<<< orphan*/  tx_pipe; } ;

/* Variables and functions */
 int gbe_txtstamp_mark_pkt (struct gbe_intf*,struct netcp_packet*) ; 

__attribute__((used)) static int gbe_txhook(int order, void *data, struct netcp_packet *p_info)
{
	struct gbe_intf *gbe_intf = data;

	p_info->tx_pipe = &gbe_intf->tx_pipe;

	return gbe_txtstamp_mark_pkt(gbe_intf, p_info);
}