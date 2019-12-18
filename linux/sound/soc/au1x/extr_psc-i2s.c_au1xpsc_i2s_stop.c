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
struct au1xpsc_audio_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2SPCR_STOP (int) ; 
 unsigned long I2SSTAT_BUSY (int) ; 
 int /*<<< orphan*/  I2S_CFG (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  I2S_PCR (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  I2S_STAT (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  PSC_CTRL (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  PSC_CTRL_SUSPEND ; 
 unsigned long PSC_I2SSTAT_RB ; 
 unsigned long PSC_I2SSTAT_TB ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int au1xpsc_i2s_stop(struct au1xpsc_audio_data *pscdata, int stype)
{
	unsigned long tmo, stat;

	__raw_writel(I2SPCR_STOP(stype), I2S_PCR(pscdata));
	wmb(); /* drain writebuffer */

	/* wait for stop confirmation */
	tmo = 1000000;
	while ((__raw_readl(I2S_STAT(pscdata)) & I2SSTAT_BUSY(stype)) && tmo)
		tmo--;

	/* if both TX and RX are idle, disable PSC */
	stat = __raw_readl(I2S_STAT(pscdata));
	if (!(stat & (PSC_I2SSTAT_TB | PSC_I2SSTAT_RB))) {
		__raw_writel(0, I2S_CFG(pscdata));
		wmb(); /* drain writebuffer */
		__raw_writel(PSC_CTRL_SUSPEND, PSC_CTRL(pscdata));
		wmb(); /* drain writebuffer */
	}
	return 0;
}