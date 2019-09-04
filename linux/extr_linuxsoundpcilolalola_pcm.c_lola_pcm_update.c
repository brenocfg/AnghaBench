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
struct lola_stream {scalar_t__ substream; scalar_t__ running; } ;
struct lola_pcm {int num_streams; struct lola_stream* streams; } ;
struct lola {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_pcm_period_elapsed (scalar_t__) ; 

void lola_pcm_update(struct lola *chip, struct lola_pcm *pcm, unsigned int bits)
{
	int i;

	for (i = 0; bits && i < pcm->num_streams; i++) {
		if (bits & (1 << i)) {
			struct lola_stream *str = &pcm->streams[i];
			if (str->substream && str->running)
				snd_pcm_period_elapsed(str->substream);
			bits &= ~(1 << i);
		}
	}
}