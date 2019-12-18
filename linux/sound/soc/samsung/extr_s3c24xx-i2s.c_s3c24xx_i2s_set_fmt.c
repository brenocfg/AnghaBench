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
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_dai {int dummy; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ S3C2410_IISMOD ; 
 int /*<<< orphan*/  S3C2410_IISMOD_MSB ; 
 int /*<<< orphan*/  S3C2410_IISMOD_SLAVE ; 
#define  SND_SOC_DAIFMT_CBM_CFM 131 
#define  SND_SOC_DAIFMT_CBS_CFS 130 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 129 
#define  SND_SOC_DAIFMT_LEFT_J 128 
 unsigned int SND_SOC_DAIFMT_MASTER_MASK ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 TYPE_1__ s3c24xx_i2s ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s3c24xx_i2s_set_fmt(struct snd_soc_dai *cpu_dai,
		unsigned int fmt)
{
	u32 iismod;

	iismod = readl(s3c24xx_i2s.regs + S3C2410_IISMOD);
	pr_debug("hw_params r: IISMOD: %x \n", iismod);

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	case SND_SOC_DAIFMT_CBM_CFM:
		iismod |= S3C2410_IISMOD_SLAVE;
		break;
	case SND_SOC_DAIFMT_CBS_CFS:
		iismod &= ~S3C2410_IISMOD_SLAVE;
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_LEFT_J:
		iismod |= S3C2410_IISMOD_MSB;
		break;
	case SND_SOC_DAIFMT_I2S:
		iismod &= ~S3C2410_IISMOD_MSB;
		break;
	default:
		return -EINVAL;
	}

	writel(iismod, s3c24xx_i2s.regs + S3C2410_IISMOD);
	pr_debug("hw_params w: IISMOD: %x \n", iismod);

	return 0;
}