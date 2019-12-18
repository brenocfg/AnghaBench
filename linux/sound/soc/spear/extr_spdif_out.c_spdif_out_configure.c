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
struct spdif_out_dev {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ SPDIF_OUT_CFG ; 
 int SPDIF_OUT_CHNLSTA_HW ; 
 int SPDIF_OUT_FDMA_TRIG_16 ; 
 scalar_t__ SPDIF_OUT_INT_EN_CLR ; 
 scalar_t__ SPDIF_OUT_INT_STA_CLR ; 
 int SPDIF_OUT_MEMFMT_16_16 ; 
 int SPDIF_OUT_PARITY_HW ; 
 int SPDIF_OUT_RESET ; 
 scalar_t__ SPDIF_OUT_SOFT_RST ; 
 int SPDIF_OUT_USER_HW ; 
 int SPDIF_OUT_VALID_HW ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void spdif_out_configure(struct spdif_out_dev *host)
{
	writel(SPDIF_OUT_RESET, host->io_base + SPDIF_OUT_SOFT_RST);
	mdelay(1);
	writel(readl(host->io_base + SPDIF_OUT_SOFT_RST) & ~SPDIF_OUT_RESET,
			host->io_base + SPDIF_OUT_SOFT_RST);

	writel(SPDIF_OUT_FDMA_TRIG_16 | SPDIF_OUT_MEMFMT_16_16 |
			SPDIF_OUT_VALID_HW | SPDIF_OUT_USER_HW |
			SPDIF_OUT_CHNLSTA_HW | SPDIF_OUT_PARITY_HW,
			host->io_base + SPDIF_OUT_CFG);

	writel(0x7F, host->io_base + SPDIF_OUT_INT_STA_CLR);
	writel(0x7F, host->io_base + SPDIF_OUT_INT_EN_CLR);
}