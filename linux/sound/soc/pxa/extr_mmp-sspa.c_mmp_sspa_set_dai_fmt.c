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
struct sspa_priv {unsigned int dai_fmt; struct ssp_device* sspa; } ;
struct ssp_device {TYPE_1__* pdev; } ;
struct snd_soc_dai {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SND_SOC_DAIFMT_CBM_CFM 131 
#define  SND_SOC_DAIFMT_CBS_CFS 130 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 129 
 unsigned int SND_SOC_DAIFMT_INV_MASK ; 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
#define  SND_SOC_DAIFMT_NB_NF 128 
 int SSPA_CTL_XDATDLY (int) ; 
 int /*<<< orphan*/  SSPA_RXCTL ; 
 int /*<<< orphan*/  SSPA_RXSP ; 
 int SSPA_SP_FFLUSH ; 
 int SSPA_SP_FSP ; 
 int SSPA_SP_FWID (int) ; 
 int SSPA_SP_MSL ; 
 int SSPA_SP_S_EN ; 
 int SSPA_SP_S_RST ; 
 int SSPA_SP_WEN ; 
 int /*<<< orphan*/  SSPA_TXCTL ; 
 int /*<<< orphan*/  SSPA_TXSP ; 
 int SSPA_TXSP_FPER (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int mmp_sspa_read_reg (struct ssp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmp_sspa_write_reg (struct ssp_device*,int /*<<< orphan*/ ,int) ; 
 struct sspa_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int mmp_sspa_set_dai_fmt(struct snd_soc_dai *cpu_dai,
				 unsigned int fmt)
{
	struct sspa_priv *sspa_priv = snd_soc_dai_get_drvdata(cpu_dai);
	struct ssp_device *sspa = sspa_priv->sspa;
	u32 sspa_sp, sspa_ctrl;

	/* check if we need to change anything at all */
	if (sspa_priv->dai_fmt == fmt)
		return 0;

	/* we can only change the settings if the port is not in use */
	if ((mmp_sspa_read_reg(sspa, SSPA_TXSP) & SSPA_SP_S_EN) ||
	    (mmp_sspa_read_reg(sspa, SSPA_RXSP) & SSPA_SP_S_EN)) {
		dev_err(&sspa->pdev->dev,
			"can't change hardware dai format: stream is in use\n");
		return -EINVAL;
	}

	/* reset port settings */
	sspa_sp   = SSPA_SP_WEN | SSPA_SP_S_RST | SSPA_SP_FFLUSH;
	sspa_ctrl = 0;

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBS_CFS:
		sspa_sp |= SSPA_SP_MSL;
		break;
	case SND_SOC_DAIFMT_CBM_CFM:
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_NB_NF:
		sspa_sp |= SSPA_SP_FSP;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		sspa_sp |= SSPA_TXSP_FPER(63);
		sspa_sp |= SSPA_SP_FWID(31);
		sspa_ctrl |= SSPA_CTL_XDATDLY(1);
		break;
	default:
		return -EINVAL;
	}

	mmp_sspa_write_reg(sspa, SSPA_TXSP, sspa_sp);
	mmp_sspa_write_reg(sspa, SSPA_RXSP, sspa_sp);

	sspa_sp &= ~(SSPA_SP_S_RST | SSPA_SP_FFLUSH);
	mmp_sspa_write_reg(sspa, SSPA_TXSP, sspa_sp);
	mmp_sspa_write_reg(sspa, SSPA_RXSP, sspa_sp);

	/*
	 * FIXME: hw issue, for the tx serial port,
	 * can not config the master/slave mode;
	 * so must clean this bit.
	 * The master/slave mode has been set in the
	 * rx port.
	 */
	sspa_sp &= ~SSPA_SP_MSL;
	mmp_sspa_write_reg(sspa, SSPA_TXSP, sspa_sp);

	mmp_sspa_write_reg(sspa, SSPA_TXCTL, sspa_ctrl);
	mmp_sspa_write_reg(sspa, SSPA_RXCTL, sspa_ctrl);

	/* Since we are configuring the timings for the format by hand
	 * we have to defer some things until hw_params() where we
	 * know parameters like the sample size.
	 */
	sspa_priv->dai_fmt = fmt;
	return 0;
}