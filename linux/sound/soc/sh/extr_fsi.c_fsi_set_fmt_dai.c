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
struct fsi_priv {int chan_num; int /*<<< orphan*/  fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR_I2S ; 
 int /*<<< orphan*/  CR_PCM ; 
 int EINVAL ; 
 unsigned int SND_SOC_DAIFMT_FORMAT_MASK ; 
#define  SND_SOC_DAIFMT_I2S 129 
#define  SND_SOC_DAIFMT_LEFT_J 128 

__attribute__((used)) static int fsi_set_fmt_dai(struct fsi_priv *fsi, unsigned int fmt)
{
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	case SND_SOC_DAIFMT_I2S:
		fsi->fmt = CR_I2S;
		fsi->chan_num = 2;
		break;
	case SND_SOC_DAIFMT_LEFT_J:
		fsi->fmt = CR_PCM;
		fsi->chan_num = 2;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}