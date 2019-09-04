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
typedef  int /*<<< orphan*/  u32 ;
struct meson_spicc_device {scalar_t__ rx_remain; } ;

/* Variables and functions */
 scalar_t__ SPICC_FIFO_HALF ; 
 int /*<<< orphan*/  SPICC_RH_EN ; 
 int /*<<< orphan*/  SPICC_RR_EN ; 

__attribute__((used)) static inline u32 meson_spicc_setup_rx_irq(struct meson_spicc_device *spicc,
					   u32 irq_ctrl)
{
	if (spicc->rx_remain > SPICC_FIFO_HALF)
		irq_ctrl |= SPICC_RH_EN;
	else
		irq_ctrl |= SPICC_RR_EN;

	return irq_ctrl;
}