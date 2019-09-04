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
struct axg_fifo {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL0_DMA_EN ; 
 int /*<<< orphan*/  FIFO_CTRL0 ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __dma_enable(struct axg_fifo *fifo,  bool enable)
{
	regmap_update_bits(fifo->map, FIFO_CTRL0, CTRL0_DMA_EN,
			   enable ? CTRL0_DMA_EN : 0);
}