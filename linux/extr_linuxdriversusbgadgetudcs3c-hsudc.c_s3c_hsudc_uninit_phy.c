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

/* Variables and functions */
 int /*<<< orphan*/  S3C2443_PHYPWR ; 
 int S3C2443_PHYPWR_FSUSPEND ; 
 int /*<<< orphan*/  S3C2443_PWRCFG ; 
 int S3C2443_PWRCFG_USBPHY ; 
 int /*<<< orphan*/  S3C2443_UCLKCON ; 
 int S3C2443_UCLKCON_FUNC_CLKEN ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c_hsudc_uninit_phy(void)
{
	u32 cfg;

	cfg = readl(S3C2443_PWRCFG) & ~S3C2443_PWRCFG_USBPHY;
	writel(cfg, S3C2443_PWRCFG);

	writel(S3C2443_PHYPWR_FSUSPEND, S3C2443_PHYPWR);

	cfg = readl(S3C2443_UCLKCON) & ~S3C2443_UCLKCON_FUNC_CLKEN;
	writel(cfg, S3C2443_UCLKCON);
}