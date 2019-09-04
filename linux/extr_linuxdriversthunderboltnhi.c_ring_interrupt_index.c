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
struct tb_ring {int hop; TYPE_1__* nhi; int /*<<< orphan*/  is_tx; } ;
struct TYPE_2__ {scalar_t__ hop_count; } ;

/* Variables and functions */

__attribute__((used)) static int ring_interrupt_index(struct tb_ring *ring)
{
	int bit = ring->hop;
	if (!ring->is_tx)
		bit += ring->nhi->hop_count;
	return bit;
}