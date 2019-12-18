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
struct ssp_priv {struct ssp_device* ssp; } ;
struct ssp_device {int dummy; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  SSSR ; 
 int /*<<< orphan*/  dump_registers (struct ssp_device*) ; 
 int /*<<< orphan*/  pxa_ssp_disable (struct ssp_device*) ; 
 int /*<<< orphan*/  pxa_ssp_enable (struct ssp_device*) ; 
 int pxa_ssp_read_reg (struct ssp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa_ssp_set_running_bit (struct snd_pcm_substream*,struct ssp_device*,int) ; 
 int /*<<< orphan*/  pxa_ssp_write_reg (struct ssp_device*,int /*<<< orphan*/ ,int) ; 
 struct ssp_priv* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int pxa_ssp_trigger(struct snd_pcm_substream *substream, int cmd,
			   struct snd_soc_dai *cpu_dai)
{
	int ret = 0;
	struct ssp_priv *priv = snd_soc_dai_get_drvdata(cpu_dai);
	struct ssp_device *ssp = priv->ssp;
	int val;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_RESUME:
		pxa_ssp_enable(ssp);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		pxa_ssp_set_running_bit(substream, ssp, 1);
		val = pxa_ssp_read_reg(ssp, SSSR);
		pxa_ssp_write_reg(ssp, SSSR, val);
		break;
	case SNDRV_PCM_TRIGGER_START:
		pxa_ssp_set_running_bit(substream, ssp, 1);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		pxa_ssp_set_running_bit(substream, ssp, 0);
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
		pxa_ssp_disable(ssp);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		pxa_ssp_set_running_bit(substream, ssp, 0);
		break;

	default:
		ret = -EINVAL;
	}

	dump_registers(ssp);

	return ret;
}