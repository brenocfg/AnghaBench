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
typedef  int u32 ;
struct snd_soc_dai {int dummy; } ;
struct s3c_i2sv2_info {struct clk* iis_pclk; struct clk* iis_cclk; scalar_t__ regs; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ S3C2412_IISMOD ; 
 int S3C2412_IISMOD_IMS_SYSMUX ; 
 int readl (scalar_t__) ; 
 struct s3c_i2sv2_info* to_info (struct snd_soc_dai*) ; 

struct clk *s3c_i2sv2_get_clock(struct snd_soc_dai *cpu_dai)
{
	struct s3c_i2sv2_info *i2s = to_info(cpu_dai);
	u32 iismod = readl(i2s->regs + S3C2412_IISMOD);

	if (iismod & S3C2412_IISMOD_IMS_SYSMUX)
		return i2s->iis_cclk;
	else
		return i2s->iis_pclk;
}