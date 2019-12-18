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
struct mp_codec_params {scalar_t__ type; scalar_t__ bits_per_coded_sample; int /*<<< orphan*/  codec_tag; int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 scalar_t__ STREAM_AUDIO ; 
 int /*<<< orphan*/  lookup_tag (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_audio_pcm_tag (struct mp_codec_params*) ; 

void mp_set_codec_from_tag(struct mp_codec_params *c)
{
    c->codec = lookup_tag(c->type, c->codec_tag);

    if (c->type == STREAM_AUDIO && c->bits_per_coded_sample)
        map_audio_pcm_tag(c);
}