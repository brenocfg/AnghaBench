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
struct snd_info_buffer {int dummy; } ;
struct TYPE_2__ {char const* expires; } ;
struct loopback_pcm {char const* pcm_buffer_size; char const* buf_pos; char const* silent_size; char const* pcm_period_size; char const* pcm_bps; char const* pcm_salign; char const* pcm_rate_shift; char const* period_update_pending; char const* irq_pos; char const* period_size_frac; TYPE_1__ timer; int /*<<< orphan*/  last_jiffies; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,...) ; 

__attribute__((used)) static void print_dpcm_info(struct snd_info_buffer *buffer,
			    struct loopback_pcm *dpcm,
			    const char *id)
{
	snd_iprintf(buffer, "  %s\n", id);
	if (dpcm == NULL) {
		snd_iprintf(buffer, "    inactive\n");
		return;
	}
	snd_iprintf(buffer, "    buffer_size:\t%u\n", dpcm->pcm_buffer_size);
	snd_iprintf(buffer, "    buffer_pos:\t\t%u\n", dpcm->buf_pos);
	snd_iprintf(buffer, "    silent_size:\t%u\n", dpcm->silent_size);
	snd_iprintf(buffer, "    period_size:\t%u\n", dpcm->pcm_period_size);
	snd_iprintf(buffer, "    bytes_per_sec:\t%u\n", dpcm->pcm_bps);
	snd_iprintf(buffer, "    sample_align:\t%u\n", dpcm->pcm_salign);
	snd_iprintf(buffer, "    rate_shift:\t\t%u\n", dpcm->pcm_rate_shift);
	snd_iprintf(buffer, "    update_pending:\t%u\n",
						dpcm->period_update_pending);
	snd_iprintf(buffer, "    irq_pos:\t\t%u\n", dpcm->irq_pos);
	snd_iprintf(buffer, "    period_frac:\t%u\n", dpcm->period_size_frac);
	snd_iprintf(buffer, "    last_jiffies:\t%lu (%lu)\n",
					dpcm->last_jiffies, jiffies);
	snd_iprintf(buffer, "    timer_expires:\t%lu\n", dpcm->timer.expires);
}