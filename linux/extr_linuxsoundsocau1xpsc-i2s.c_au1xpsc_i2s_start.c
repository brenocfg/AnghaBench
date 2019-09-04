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
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I2SPCR_CLRFIFO (int) ; 
 int /*<<< orphan*/  I2SPCR_START (int) ; 
 int /*<<< orphan*/  I2SPCR_STOP (int) ; 
 unsigned long I2SSTAT_BUSY (int) ; 
 int /*<<< orphan*/  I2S_PCR (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  I2S_STAT (struct au1xpsc_audio_data*) ; 
 unsigned long PSC_I2SSTAT_RB ; 
 unsigned long PSC_I2SSTAT_TB ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int au1xpsc_i2s_configure (struct au1xpsc_audio_data*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int au1xpsc_i2s_start(struct au1xpsc_audio_data *pscdata, int stype)
{
	unsigned long tmo, stat;
	int ret;

	ret = 0;

	/* if both TX and RX are idle, configure the PSC  */
	stat = __raw_readl(I2S_STAT(pscdata));
	if (!(stat & (PSC_I2SSTAT_TB | PSC_I2SSTAT_RB))) {
		ret = au1xpsc_i2s_configure(pscdata);
		if (ret)
			goto out;
	}

	__raw_writel(I2SPCR_CLRFIFO(stype), I2S_PCR(pscdata));
	wmb(); /* drain writebuffer */
	__raw_writel(I2SPCR_START(stype), I2S_PCR(pscdata));
	wmb(); /* drain writebuffer */

	/* wait for start confirmation */
	tmo = 1000000;
	while (!(__raw_readl(I2S_STAT(pscdata)) & I2SSTAT_BUSY(stype)) && tmo)
		tmo--;

	if (!tmo) {
		__raw_writel(I2SPCR_STOP(stype), I2S_PCR(pscdata));
		wmb(); /* drain writebuffer */
		ret = -ETIMEDOUT;
	}
out:
	return ret;
}