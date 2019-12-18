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
struct mp_aframe {TYPE_1__* av_frame; int /*<<< orphan*/  format; int /*<<< orphan*/  chmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  channels; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  format; int /*<<< orphan*/  sample_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  mp_aframe_copy_attributes (struct mp_aframe*,struct mp_aframe*) ; 
 int /*<<< orphan*/  mp_aframe_reset (struct mp_aframe*) ; 

void mp_aframe_config_copy(struct mp_aframe *dst, struct mp_aframe *src)
{
    mp_aframe_reset(dst);

    dst->chmap = src->chmap;
    dst->format = src->format;

    mp_aframe_copy_attributes(dst, src);

    dst->av_frame->sample_rate = src->av_frame->sample_rate;
    dst->av_frame->format = src->av_frame->format;
    dst->av_frame->channel_layout = src->av_frame->channel_layout;
#if LIBAVUTIL_VERSION_MICRO >= 100
    // FFmpeg being a stupid POS again
    dst->av_frame->channels = src->av_frame->channels;
#endif
}