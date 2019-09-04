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
typedef  int u32 ;
struct pic32_spi {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int STAT_RF_LVL_MASK ; 
 int STAT_RF_LVL_SHIFT ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 pic32_rx_fifo_level(struct pic32_spi *pic32s)
{
	u32 sr = readl(&pic32s->regs->status);

	return (sr >> STAT_RF_LVL_SHIFT) & STAT_RF_LVL_MASK;
}