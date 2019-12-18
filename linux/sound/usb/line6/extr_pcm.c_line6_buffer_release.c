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
struct snd_line6_pcm {int dummy; } ;
struct line6_pcm_stream {int /*<<< orphan*/ * buffer; int /*<<< orphan*/  opened; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  line6_wait_clear_audio_urbs (struct snd_line6_pcm*,struct line6_pcm_stream*) ; 

__attribute__((used)) static void line6_buffer_release(struct snd_line6_pcm *line6pcm,
				 struct line6_pcm_stream *pstr, int type)
{
	clear_bit(type, &pstr->opened);
	if (!pstr->opened) {
		line6_wait_clear_audio_urbs(line6pcm, pstr);
		kfree(pstr->buffer);
		pstr->buffer = NULL;
	}
}