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
 int /*<<< orphan*/  S3C2440_IISMOD_MPLL ; 
#define  S3C24XX_CLKSRC_MPLL 129 
#define  S3C24XX_CLKSRC_PCLK 128 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 TYPE_1__ s3c24xx_i2s ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s3c24xx_i2s_set_sysclk(struct snd_soc_dai *cpu_dai,
	int clk_id, unsigned int freq, int dir)
{
	u32 iismod = readl(s3c24xx_i2s.regs + S3C2410_IISMOD);

	iismod &= ~S3C2440_IISMOD_MPLL;

	switch (clk_id) {
	case S3C24XX_CLKSRC_PCLK:
		break;
	case S3C24XX_CLKSRC_MPLL:
		iismod |= S3C2440_IISMOD_MPLL;
		break;
	default:
		return -EINVAL;
	}

	writel(iismod, s3c24xx_i2s.regs + S3C2410_IISMOD);
	return 0;
}