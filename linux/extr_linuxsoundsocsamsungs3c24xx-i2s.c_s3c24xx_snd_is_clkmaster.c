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
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ S3C2410_IISMOD ; 
 int S3C2410_IISMOD_SLAVE ; 
 int readl (scalar_t__) ; 
 TYPE_1__ s3c24xx_i2s ; 

__attribute__((used)) static inline int s3c24xx_snd_is_clkmaster(void)
{
	return (readl(s3c24xx_i2s.regs + S3C2410_IISMOD) & S3C2410_IISMOD_SLAVE) ? 0:1;
}