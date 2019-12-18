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
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSL_FMT_RECEIVER ; 
 int /*<<< orphan*/  FSL_FMT_TRANSMITTER ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int fsl_sai_set_dai_fmt_tr (struct snd_soc_dai*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsl_sai_set_dai_fmt(struct snd_soc_dai *cpu_dai, unsigned int fmt)
{
	int ret;

	ret = fsl_sai_set_dai_fmt_tr(cpu_dai, fmt, FSL_FMT_TRANSMITTER);
	if (ret) {
		dev_err(cpu_dai->dev, "Cannot set tx format: %d\n", ret);
		return ret;
	}

	ret = fsl_sai_set_dai_fmt_tr(cpu_dai, fmt, FSL_FMT_RECEIVER);
	if (ret)
		dev_err(cpu_dai->dev, "Cannot set rx format: %d\n", ret);

	return ret;
}