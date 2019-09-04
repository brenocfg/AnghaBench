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
struct meson_spicc_device {scalar_t__ base; scalar_t__ rx_remain; } ;

/* Variables and functions */
 scalar_t__ SPICC_RXDATA ; 
 int /*<<< orphan*/  meson_spicc_push_data (struct meson_spicc_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ meson_spicc_rxready (struct meson_spicc_device*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static inline void meson_spicc_rx(struct meson_spicc_device *spicc)
{
	/* Empty RX FIFO */
	while (spicc->rx_remain &&
	       meson_spicc_rxready(spicc))
		meson_spicc_push_data(spicc,
				readl_relaxed(spicc->base + SPICC_RXDATA));
}