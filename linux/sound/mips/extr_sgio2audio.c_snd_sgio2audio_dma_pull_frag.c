#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct snd_sgio2audio {TYPE_5__* channel; scalar_t__ ring_base; } ;
struct snd_pcm_runtime {unsigned char* dma_area; scalar_t__ period_size; int /*<<< orphan*/  buffer_size; } ;
typedef  int s16 ;
struct TYPE_9__ {TYPE_2__* chan; } ;
struct TYPE_10__ {TYPE_3__ audio; } ;
struct TYPE_12__ {TYPE_4__ perif; } ;
struct TYPE_11__ {int pos; int /*<<< orphan*/  lock; scalar_t__ size; TYPE_1__* substream; } ;
struct TYPE_8__ {int /*<<< orphan*/  read_ptr; } ;
struct TYPE_7__ {struct snd_pcm_runtime* runtime; } ;

/* Variables and functions */
 int CHANNEL_LEFT_SHIFT ; 
 int CHANNEL_RIGHT_SHIFT ; 
 unsigned long CHANNEL_RING_MASK ; 
 unsigned int CHANNEL_RING_SHIFT ; 
 int frames_to_bytes (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 TYPE_6__* mace ; 
 unsigned long readq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writeq (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_sgio2audio_dma_pull_frag(struct snd_sgio2audio *chip,
					unsigned int ch, unsigned int count)
{
	int ret;
	unsigned long src_base, src_pos, dst_mask;
	unsigned char *dst_base;
	int dst_pos;
	u64 *src;
	s16 *dst;
	u64 x;
	unsigned long flags;
	struct snd_pcm_runtime *runtime = chip->channel[ch].substream->runtime;

	spin_lock_irqsave(&chip->channel[ch].lock, flags);

	src_base = (unsigned long) chip->ring_base | (ch << CHANNEL_RING_SHIFT);
	src_pos = readq(&mace->perif.audio.chan[ch].read_ptr);
	dst_base = runtime->dma_area;
	dst_pos = chip->channel[ch].pos;
	dst_mask = frames_to_bytes(runtime, runtime->buffer_size) - 1;

	/* check if a period has elapsed */
	chip->channel[ch].size += (count >> 3); /* in frames */
	ret = chip->channel[ch].size >= runtime->period_size;
	chip->channel[ch].size %= runtime->period_size;

	while (count) {
		src = (u64 *)(src_base + src_pos);
		dst = (s16 *)(dst_base + dst_pos);

		x = *src;
		dst[0] = (x >> CHANNEL_LEFT_SHIFT) & 0xffff;
		dst[1] = (x >> CHANNEL_RIGHT_SHIFT) & 0xffff;

		src_pos = (src_pos + sizeof(u64)) & CHANNEL_RING_MASK;
		dst_pos = (dst_pos + 2 * sizeof(s16)) & dst_mask;
		count -= sizeof(u64);
	}

	writeq(src_pos, &mace->perif.audio.chan[ch].read_ptr); /* in bytes */
	chip->channel[ch].pos = dst_pos;

	spin_unlock_irqrestore(&chip->channel[ch].lock, flags);
	return ret;
}