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
struct snd_pcm_substream {int dummy; } ;
struct fsl_micfil {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct fsl_micfil* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int fsl_micfil_startup(struct snd_pcm_substream *substream,
			      struct snd_soc_dai *dai)
{
	struct fsl_micfil *micfil = snd_soc_dai_get_drvdata(dai);

	if (!micfil) {
		dev_err(dai->dev,
			"micfil dai priv_data not set\n");
		return -EINVAL;
	}

	return 0;
}