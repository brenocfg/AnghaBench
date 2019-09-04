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
typedef  int uint32_t ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; } ;
struct q6asm_dai_rtd {int /*<<< orphan*/  audio_client; int /*<<< orphan*/  state; int /*<<< orphan*/  pcm_count; int /*<<< orphan*/  pcm_irq_pos; struct snd_pcm_substream* substream; } ;

/* Variables and functions */
#define  ASM_CLIENT_EVENT_CMD_EOS_DONE 131 
#define  ASM_CLIENT_EVENT_CMD_RUN_DONE 130 
#define  ASM_CLIENT_EVENT_DATA_READ_DONE 129 
#define  ASM_CLIENT_EVENT_DATA_WRITE_DONE 128 
 int /*<<< orphan*/  NO_TIMESTAMP ; 
 int /*<<< orphan*/  Q6ASM_STREAM_RUNNING ; 
 int /*<<< orphan*/  Q6ASM_STREAM_STOPPED ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  q6asm_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q6asm_write_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 

__attribute__((used)) static void event_handler(uint32_t opcode, uint32_t token,
			  uint32_t *payload, void *priv)
{
	struct q6asm_dai_rtd *prtd = priv;
	struct snd_pcm_substream *substream = prtd->substream;

	switch (opcode) {
	case ASM_CLIENT_EVENT_CMD_RUN_DONE:
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			q6asm_write_async(prtd->audio_client,
				   prtd->pcm_count, 0, 0, NO_TIMESTAMP);
		break;
	case ASM_CLIENT_EVENT_CMD_EOS_DONE:
		prtd->state = Q6ASM_STREAM_STOPPED;
		break;
	case ASM_CLIENT_EVENT_DATA_WRITE_DONE: {
		prtd->pcm_irq_pos += prtd->pcm_count;
		snd_pcm_period_elapsed(substream);
		if (prtd->state == Q6ASM_STREAM_RUNNING)
			q6asm_write_async(prtd->audio_client,
					   prtd->pcm_count, 0, 0, NO_TIMESTAMP);

		break;
		}
	case ASM_CLIENT_EVENT_DATA_READ_DONE:
		prtd->pcm_irq_pos += prtd->pcm_count;
		snd_pcm_period_elapsed(substream);
		if (prtd->state == Q6ASM_STREAM_RUNNING)
			q6asm_read(prtd->audio_client);

		break;
	default:
		break;
	}
}