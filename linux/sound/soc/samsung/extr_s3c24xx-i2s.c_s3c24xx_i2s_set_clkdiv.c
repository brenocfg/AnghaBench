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
struct snd_soc_dai {int dummy; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ S3C2410_IISCON ; 
 int S3C2410_IISCON_PSCEN ; 
 scalar_t__ S3C2410_IISMOD ; 
 int S3C2410_IISMOD_384FS ; 
 int S3C2410_IISMOD_FS_MASK ; 
 scalar_t__ S3C2410_IISPSR ; 
#define  S3C24XX_DIV_BCLK 130 
#define  S3C24XX_DIV_MCLK 129 
#define  S3C24XX_DIV_PRESCALER 128 
 int readl (scalar_t__) ; 
 TYPE_1__ s3c24xx_i2s ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int s3c24xx_i2s_set_clkdiv(struct snd_soc_dai *cpu_dai,
	int div_id, int div)
{
	u32 reg;

	switch (div_id) {
	case S3C24XX_DIV_BCLK:
		reg = readl(s3c24xx_i2s.regs + S3C2410_IISMOD) & ~S3C2410_IISMOD_FS_MASK;
		writel(reg | div, s3c24xx_i2s.regs + S3C2410_IISMOD);
		break;
	case S3C24XX_DIV_MCLK:
		reg = readl(s3c24xx_i2s.regs + S3C2410_IISMOD) & ~(S3C2410_IISMOD_384FS);
		writel(reg | div, s3c24xx_i2s.regs + S3C2410_IISMOD);
		break;
	case S3C24XX_DIV_PRESCALER:
		writel(div, s3c24xx_i2s.regs + S3C2410_IISPSR);
		reg = readl(s3c24xx_i2s.regs + S3C2410_IISCON);
		writel(reg | S3C2410_IISCON_PSCEN, s3c24xx_i2s.regs + S3C2410_IISCON);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}