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
typedef  int /*<<< orphan*/  u8 ;
struct axg_fifo {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL1_INT_CLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIFO_CTRL1 ; 
 int /*<<< orphan*/  FIFO_INT_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void axg_fifo_ack_irq(struct axg_fifo *fifo, u8 mask)
{
	regmap_update_bits(fifo->map, FIFO_CTRL1,
			   CTRL1_INT_CLR(FIFO_INT_MASK),
			   CTRL1_INT_CLR(mask));

	/* Clear must also be cleared */
	regmap_update_bits(fifo->map, FIFO_CTRL1,
			   CTRL1_INT_CLR(FIFO_INT_MASK),
			   0);
}