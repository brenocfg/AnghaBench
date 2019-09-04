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
struct snd_pcm_substream {int /*<<< orphan*/  runtime; } ;
struct lola_stream {unsigned int bufsize; int /*<<< orphan*/  dsd; } ;
struct lola {int dummy; } ;
typedef  int /*<<< orphan*/  snd_pcm_uframes_t ;

/* Variables and functions */
 int /*<<< orphan*/  LPIB ; 
 int /*<<< orphan*/  bytes_to_frames (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int lola_dsd_read (struct lola*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct lola_stream* lola_get_stream (struct snd_pcm_substream*) ; 
 struct lola* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t lola_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct lola *chip = snd_pcm_substream_chip(substream);
	struct lola_stream *str = lola_get_stream(substream);
	unsigned int pos = lola_dsd_read(chip, str->dsd, LPIB);

	if (pos >= str->bufsize)
		pos = 0;
	return bytes_to_frames(substream->runtime, pos);
}