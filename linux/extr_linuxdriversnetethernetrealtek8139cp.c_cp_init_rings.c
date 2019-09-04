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
struct cp_private {TYPE_1__* tx_opts; TYPE_1__* tx_ring; } ;
struct cp_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  opts1; } ;

/* Variables and functions */
 int CP_TX_RING_SIZE ; 
 int /*<<< orphan*/  RingEnd ; 
 int /*<<< orphan*/  cp_init_rings_index (struct cp_private*) ; 
 int cp_refill_rx (struct cp_private*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cp_init_rings (struct cp_private *cp)
{
	memset(cp->tx_ring, 0, sizeof(struct cp_desc) * CP_TX_RING_SIZE);
	cp->tx_ring[CP_TX_RING_SIZE - 1].opts1 = cpu_to_le32(RingEnd);
	memset(cp->tx_opts, 0, sizeof(cp->tx_opts));

	cp_init_rings_index(cp);

	return cp_refill_rx (cp);
}