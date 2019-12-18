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
struct TYPE_2__ {int format; unsigned int samples_per_sec; int speakers; scalar_t__* data; } ;
struct vlc_source {TYPE_1__ audio; scalar_t__ audio_capacity; } ;
typedef  enum speaker_layout { ____Placeholder_speaker_layout } speaker_layout ;
typedef  enum audio_format { ____Placeholder_audio_format } audio_format ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (void*) ; 
 int convert_vlc_audio_format (char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vlcs_audio_setup(void **p_data, char *format, unsigned *rate,
			    unsigned *channels)
{
	struct vlc_source *c = *p_data;
	enum audio_format new_audio_format;

	new_audio_format = convert_vlc_audio_format(format);
	if (*channels > 2)
		*channels = 2;

	/* don't free audio data if the data is the same format */
	if (c->audio.format == new_audio_format &&
	    c->audio.samples_per_sec == *rate &&
	    c->audio.speakers == (enum speaker_layout) * channels)
		return 0;

	c->audio_capacity = 0;
	bfree((void *)c->audio.data[0]);

	memset(&c->audio, 0, sizeof(c->audio));
	c->audio.speakers = (enum speaker_layout) * channels;
	c->audio.samples_per_sec = *rate;
	c->audio.format = new_audio_format;
	return 0;
}