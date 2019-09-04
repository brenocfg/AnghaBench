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
struct snd_soc_dai {int dummy; } ;
struct fsl_ssi {int dummy; } ;

/* Variables and functions */
 int _fsl_ssi_set_dai_fmt (struct fsl_ssi*,unsigned int) ; 
 scalar_t__ fsl_ssi_is_ac97 (struct fsl_ssi*) ; 
 struct fsl_ssi* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_ssi_set_dai_fmt(struct snd_soc_dai *dai, unsigned int fmt)
{
	struct fsl_ssi *ssi = snd_soc_dai_get_drvdata(dai);

	/* AC97 configured DAIFMT earlier in the probe() */
	if (fsl_ssi_is_ac97(ssi))
		return 0;

	return _fsl_ssi_set_dai_fmt(ssi, fmt);
}