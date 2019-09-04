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
struct cp_private {scalar_t__ tx_tail; scalar_t__ tx_head; scalar_t__ rx_tail; } ;

/* Variables and functions */

__attribute__((used)) static void cp_init_rings_index (struct cp_private *cp)
{
	cp->rx_tail = 0;
	cp->tx_head = cp->tx_tail = 0;
}