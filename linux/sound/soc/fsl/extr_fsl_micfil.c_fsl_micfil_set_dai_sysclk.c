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
struct snd_soc_dai {int dummy; } ;
struct fsl_micfil {int /*<<< orphan*/  mclk; TYPE_1__* pdev; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int fsl_micfil_set_mclk_rate (struct fsl_micfil*,unsigned int) ; 
 struct fsl_micfil* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_micfil_set_dai_sysclk(struct snd_soc_dai *dai, int clk_id,
				     unsigned int freq, int dir)
{
	struct fsl_micfil *micfil = snd_soc_dai_get_drvdata(dai);
	struct device *dev = &micfil->pdev->dev;

	int ret;

	if (!freq)
		return 0;

	ret = fsl_micfil_set_mclk_rate(micfil, freq);
	if (ret < 0)
		dev_err(dev, "failed to set mclk[%lu] to rate %u\n",
			clk_get_rate(micfil->mclk), freq);

	return ret;
}