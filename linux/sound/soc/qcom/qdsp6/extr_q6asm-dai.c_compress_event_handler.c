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
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct snd_compr_stream {int dummy; } ;
struct q6asm_dai_rtd {int /*<<< orphan*/  lock; scalar_t__ pcm_count; scalar_t__ bytes_sent; int /*<<< orphan*/  audio_client; scalar_t__ bytes_received; int /*<<< orphan*/  state; scalar_t__ copied_total; struct snd_compr_stream* cstream; } ;

/* Variables and functions */
#define  ASM_CLIENT_EVENT_CMD_EOS_DONE 130 
#define  ASM_CLIENT_EVENT_CMD_RUN_DONE 129 
#define  ASM_CLIENT_EVENT_DATA_WRITE_DONE 128 
 int /*<<< orphan*/  NO_TIMESTAMP ; 
 int /*<<< orphan*/  Q6ASM_STREAM_RUNNING ; 
 int /*<<< orphan*/  Q6ASM_STREAM_STOPPED ; 
 int /*<<< orphan*/  q6asm_write_async (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_compr_fragment_elapsed (struct snd_compr_stream*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void compress_event_handler(uint32_t opcode, uint32_t token,
				   uint32_t *payload, void *priv)
{
	struct q6asm_dai_rtd *prtd = priv;
	struct snd_compr_stream *substream = prtd->cstream;
	unsigned long flags;
	uint64_t avail;

	switch (opcode) {
	case ASM_CLIENT_EVENT_CMD_RUN_DONE:
		spin_lock_irqsave(&prtd->lock, flags);
		if (!prtd->bytes_sent) {
			q6asm_write_async(prtd->audio_client, prtd->pcm_count,
					  0, 0, NO_TIMESTAMP);
			prtd->bytes_sent += prtd->pcm_count;
		}

		spin_unlock_irqrestore(&prtd->lock, flags);
		break;

	case ASM_CLIENT_EVENT_CMD_EOS_DONE:
		prtd->state = Q6ASM_STREAM_STOPPED;
		break;

	case ASM_CLIENT_EVENT_DATA_WRITE_DONE:
		spin_lock_irqsave(&prtd->lock, flags);

		prtd->copied_total += prtd->pcm_count;
		snd_compr_fragment_elapsed(substream);

		if (prtd->state != Q6ASM_STREAM_RUNNING) {
			spin_unlock_irqrestore(&prtd->lock, flags);
			break;
		}

		avail = prtd->bytes_received - prtd->bytes_sent;

		if (avail >= prtd->pcm_count) {
			q6asm_write_async(prtd->audio_client,
					   prtd->pcm_count, 0, 0, NO_TIMESTAMP);
			prtd->bytes_sent += prtd->pcm_count;
		}

		spin_unlock_irqrestore(&prtd->lock, flags);
		break;

	default:
		break;
	}
}