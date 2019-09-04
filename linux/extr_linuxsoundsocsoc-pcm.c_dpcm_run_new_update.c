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
struct snd_soc_pcm_runtime {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_DPCM_UPDATE_BE ; 
 int /*<<< orphan*/  SND_SOC_DPCM_UPDATE_NO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dpcm_run_update_startup (struct snd_soc_pcm_runtime*,int) ; 
 int /*<<< orphan*/  dpcm_set_fe_update_state (struct snd_soc_pcm_runtime*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpcm_run_new_update(struct snd_soc_pcm_runtime *fe, int stream)
{
	int ret;

	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_BE);
	ret = dpcm_run_update_startup(fe, stream);
	if (ret < 0)
		dev_err(fe->dev, "ASoC: failed to startup some BEs\n");
	dpcm_set_fe_update_state(fe, stream, SND_SOC_DPCM_UPDATE_NO);

	return ret;
}