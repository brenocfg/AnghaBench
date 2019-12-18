#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {TYPE_1__* runtime; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct atiixp_dma {size_t ac97_pcm_type; int pcm_open_flag; int /*<<< orphan*/  buf_bytes; int /*<<< orphan*/  buf_addr; } ;
struct atiixp {struct ac97_pcm** pcms; } ;
struct ac97_pcm {TYPE_2__* r; } ;
struct TYPE_4__ {int /*<<< orphan*/  slots; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma_addr; struct atiixp_dma* private_data; } ;

/* Variables and functions */
 int atiixp_build_dma_packets (struct atiixp*,struct atiixp_dma*,struct snd_pcm_substream*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_channels (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_period_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_periods (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_ac97_pcm_close (struct ac97_pcm*) ; 
 int snd_ac97_pcm_open (struct ac97_pcm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_lib_malloc_pages (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 struct atiixp* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_atiixp_pcm_hw_params(struct snd_pcm_substream *substream,
				    struct snd_pcm_hw_params *hw_params)
{
	struct atiixp *chip = snd_pcm_substream_chip(substream);
	struct atiixp_dma *dma = substream->runtime->private_data;
	int err;

	err = snd_pcm_lib_malloc_pages(substream, params_buffer_bytes(hw_params));
	if (err < 0)
		return err;
	dma->buf_addr = substream->runtime->dma_addr;
	dma->buf_bytes = params_buffer_bytes(hw_params);

	err = atiixp_build_dma_packets(chip, dma, substream,
				       params_periods(hw_params),
				       params_period_bytes(hw_params));
	if (err < 0)
		return err;

	if (dma->ac97_pcm_type >= 0) {
		struct ac97_pcm *pcm = chip->pcms[dma->ac97_pcm_type];
		/* PCM is bound to AC97 codec(s)
		 * set up the AC97 codecs
		 */
		if (dma->pcm_open_flag) {
			snd_ac97_pcm_close(pcm);
			dma->pcm_open_flag = 0;
		}
		err = snd_ac97_pcm_open(pcm, params_rate(hw_params),
					params_channels(hw_params),
					pcm->r[0].slots);
		if (err >= 0)
			dma->pcm_open_flag = 1;
	}

	return err;
}