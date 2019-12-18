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
typedef  int u32 ;
struct spdif_in_dev {scalar_t__ io_base; } ;

/* Variables and functions */
 int SPDIF_FIFO_THRES_16 ; 
 int SPDIF_IN_BLKEN ; 
 scalar_t__ SPDIF_IN_CTRL ; 
 scalar_t__ SPDIF_IN_IRQ_MASK ; 
 int SPDIF_IN_PRTYEN ; 
 int SPDIF_IN_STATEN ; 
 int SPDIF_IN_USREN ; 
 int SPDIF_IN_VALEN ; 
 int SPDIF_MODE_16BIT ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void spdif_in_configure(struct spdif_in_dev *host)
{
	u32 ctrl = SPDIF_IN_PRTYEN | SPDIF_IN_STATEN | SPDIF_IN_USREN |
		SPDIF_IN_VALEN | SPDIF_IN_BLKEN;
	ctrl |= SPDIF_MODE_16BIT | SPDIF_FIFO_THRES_16;

	writel(ctrl, host->io_base + SPDIF_IN_CTRL);
	writel(0xF, host->io_base + SPDIF_IN_IRQ_MASK);
}