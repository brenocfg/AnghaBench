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
struct sis190_private {scalar_t__ cur_rx; scalar_t__ cur_tx; scalar_t__ dirty_rx; scalar_t__ dirty_tx; } ;

/* Variables and functions */

__attribute__((used)) static void sis190_init_ring_indexes(struct sis190_private *tp)
{
	tp->dirty_tx = tp->dirty_rx = tp->cur_tx = tp->cur_rx = 0;
}