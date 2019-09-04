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
typedef  int u16 ;
typedef  int /*<<< orphan*/  port_t ;
struct TYPE_2__ {int rx_ring_buffers; int tx_ring_buffers; } ;

/* Variables and functions */
 int log_node (int /*<<< orphan*/ *) ; 
 TYPE_1__* port_to_card (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u16 desc_abs_number(port_t *port, u16 desc, int transmit)
{
	u16 rx_buffs = port_to_card(port)->rx_ring_buffers;
	u16 tx_buffs = port_to_card(port)->tx_ring_buffers;

	desc %= (transmit ? tx_buffs : rx_buffs); // called with "X + 1" etc.
	return log_node(port) * (rx_buffs + tx_buffs) +
		transmit * rx_buffs + desc;
}