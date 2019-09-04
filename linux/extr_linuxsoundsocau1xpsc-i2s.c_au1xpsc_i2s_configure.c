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
struct au1xpsc_audio_data {int cfg; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I2S_CFG (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  I2S_STAT (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  PSC_CTRL (struct au1xpsc_audio_data*) ; 
 int PSC_CTRL_ENABLE ; 
 int PSC_CTRL_SUSPEND ; 
 int PSC_I2SCFG_DE_ENABLE ; 
 int PSC_I2SSTAT_DR ; 
 int PSC_I2SSTAT_SR ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int au1xpsc_i2s_configure(struct au1xpsc_audio_data *pscdata)
{
	unsigned long tmo;

	/* bring PSC out of sleep, and configure I2S unit */
	__raw_writel(PSC_CTRL_ENABLE, PSC_CTRL(pscdata));
	wmb(); /* drain writebuffer */

	tmo = 1000000;
	while (!(__raw_readl(I2S_STAT(pscdata)) & PSC_I2SSTAT_SR) && tmo)
		tmo--;

	if (!tmo)
		goto psc_err;

	__raw_writel(0, I2S_CFG(pscdata));
	wmb(); /* drain writebuffer */
	__raw_writel(pscdata->cfg | PSC_I2SCFG_DE_ENABLE, I2S_CFG(pscdata));
	wmb(); /* drain writebuffer */

	/* wait for I2S controller to become ready */
	tmo = 1000000;
	while (!(__raw_readl(I2S_STAT(pscdata)) & PSC_I2SSTAT_DR) && tmo)
		tmo--;

	if (tmo)
		return 0;

psc_err:
	__raw_writel(0, I2S_CFG(pscdata));
	__raw_writel(PSC_CTRL_SUSPEND, PSC_CTRL(pscdata));
	wmb(); /* drain writebuffer */
	return -ETIMEDOUT;
}