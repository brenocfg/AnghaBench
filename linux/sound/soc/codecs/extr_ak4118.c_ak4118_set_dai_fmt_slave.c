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
struct ak4118_priv {int dummy; } ;

/* Variables and functions */
 int AK4118_REG_FORMAT_CTL_DIF0 ; 
 int AK4118_REG_FORMAT_CTL_DIF1 ; 
 int AK4118_REG_FORMAT_CTL_DIF2 ; 
 int ENOTSUPP ; 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 129 
#define  SND_SOC_DAIFMT_LEFT_J 128 

__attribute__((used)) static int ak4118_set_dai_fmt_slave(struct ak4118_priv *ak4118,
				    unsigned int format)
{
	int dif;

	switch (format & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		dif = AK4118_REG_FORMAT_CTL_DIF0 | AK4118_REG_FORMAT_CTL_DIF1 |
		      AK4118_REG_FORMAT_CTL_DIF2;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		dif = AK4118_REG_FORMAT_CTL_DIF1 | AK4118_REG_FORMAT_CTL_DIF2;
		break;
	default:
		return -ENOTSUPP;
	}

	return dif;
}