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
 int ETIMEDOUT ; 
 scalar_t__ S3C2410_IISCON ; 
 int S3C2410_IISCON_LRINDEX ; 
 int readl (scalar_t__) ; 
 TYPE_1__ s3c24xx_i2s ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int s3c24xx_snd_lrsync(void)
{
	u32 iiscon;
	int timeout = 50; /* 5ms */

	while (1) {
		iiscon = readl(s3c24xx_i2s.regs + S3C2410_IISCON);
		if (iiscon & S3C2410_IISCON_LRINDEX)
			break;

		if (!timeout--)
			return -ETIMEDOUT;
		udelay(100);
	}

	return 0;
}