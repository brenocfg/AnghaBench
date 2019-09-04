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
struct mtk_eth {TYPE_1__* phy; int /*<<< orphan*/ * link; } ;
struct TYPE_2__ {scalar_t__* duplex; int /*<<< orphan*/ * speed; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 int /*<<< orphan*/  mt7620_print_link_state (struct mtk_eth*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void mt7620_mdio_link_adjust(struct mtk_eth *eth, int port)
{
	mt7620_print_link_state(eth, port, eth->link[port],
				eth->phy->speed[port],
				(eth->phy->duplex[port] == DUPLEX_FULL));
}