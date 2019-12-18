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
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ S3C2410_IISCON ; 
 int S3C2410_IISCON_IISEN ; 
 int S3C2410_IISCON_RXDMAEN ; 
 int S3C2410_IISCON_RXIDLE ; 
 scalar_t__ S3C2410_IISFCON ; 
 int S3C2410_IISFCON_RXDMA ; 
 int S3C2410_IISFCON_RXENABLE ; 
 scalar_t__ S3C2410_IISMOD ; 
 int S3C2410_IISMOD_RXMODE ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int) ; 
 int readl (scalar_t__) ; 
 TYPE_1__ s3c24xx_i2s ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void s3c24xx_snd_rxctrl(int on)
{
	u32 iisfcon;
	u32 iiscon;
	u32 iismod;

	iisfcon = readl(s3c24xx_i2s.regs + S3C2410_IISFCON);
	iiscon  = readl(s3c24xx_i2s.regs + S3C2410_IISCON);
	iismod  = readl(s3c24xx_i2s.regs + S3C2410_IISMOD);

	pr_debug("r: IISCON: %x IISMOD: %x IISFCON: %x\n", iiscon, iismod, iisfcon);

	if (on) {
		iisfcon |= S3C2410_IISFCON_RXDMA | S3C2410_IISFCON_RXENABLE;
		iiscon  |= S3C2410_IISCON_RXDMAEN | S3C2410_IISCON_IISEN;
		iiscon  &= ~S3C2410_IISCON_RXIDLE;
		iismod  |= S3C2410_IISMOD_RXMODE;

		writel(iismod,  s3c24xx_i2s.regs + S3C2410_IISMOD);
		writel(iisfcon, s3c24xx_i2s.regs + S3C2410_IISFCON);
		writel(iiscon,  s3c24xx_i2s.regs + S3C2410_IISCON);
	} else {
		/* note, we have to disable the FIFOs otherwise bad things
		 * seem to happen when the DMA stops. According to the
		 * Samsung supplied kernel, this should allow the DMA
		 * engine and FIFOs to reset. If this isn't allowed, the
		 * DMA engine will simply freeze randomly.
		 */

		iisfcon &= ~S3C2410_IISFCON_RXENABLE;
		iisfcon &= ~S3C2410_IISFCON_RXDMA;
		iiscon  |= S3C2410_IISCON_RXIDLE;
		iiscon  &= ~S3C2410_IISCON_RXDMAEN;
		iismod  &= ~S3C2410_IISMOD_RXMODE;

		writel(iisfcon, s3c24xx_i2s.regs + S3C2410_IISFCON);
		writel(iiscon,  s3c24xx_i2s.regs + S3C2410_IISCON);
		writel(iismod,  s3c24xx_i2s.regs + S3C2410_IISMOD);
	}

	pr_debug("w: IISCON: %x IISMOD: %x IISFCON: %x\n", iiscon, iismod, iisfcon);
}