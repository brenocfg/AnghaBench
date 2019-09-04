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
struct msdc_host {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MSDC_INT ; 
 scalar_t__ MSDC_INTEN ; 
 int /*<<< orphan*/  msdc_enable_cd_irq (struct msdc_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  sdr_clr_bits (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void msdc_deinit_hw(struct msdc_host *host)
{
	/* Disable and clear all interrupts */
	sdr_clr_bits(host->base + MSDC_INTEN, readl(host->base + MSDC_INTEN));
	writel(readl(host->base + MSDC_INT), host->base + MSDC_INT);

	/* Disable card detection */
	msdc_enable_cd_irq(host, 0);
	// msdc_set_power_mode(host, MMC_POWER_OFF);   /* make sure power down */ /* --- by chhung */
}