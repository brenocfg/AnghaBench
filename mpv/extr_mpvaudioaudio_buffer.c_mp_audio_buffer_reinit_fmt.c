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
struct mp_chmap {int num; } ;
struct mp_audio_buffer {int format; int srate; int sstride; int num_planes; struct mp_chmap channels; scalar_t__ num_samples; scalar_t__ allocated; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int MP_NUM_CHANNELS ; 
 int /*<<< orphan*/  TA_FREEP (int /*<<< orphan*/ *) ; 
 scalar_t__ af_fmt_is_planar (int) ; 
 int af_fmt_to_bytes (int) ; 

void mp_audio_buffer_reinit_fmt(struct mp_audio_buffer *ab, int format,
                                const struct mp_chmap *channels, int srate)
{
    for (int n = 0; n < MP_NUM_CHANNELS; n++)
        TA_FREEP(&ab->data[n]);
    ab->format = format;
    ab->channels = *channels;
    ab->srate = srate;
    ab->allocated = 0;
    ab->num_samples = 0;
    ab->sstride = af_fmt_to_bytes(ab->format);
    ab->num_planes = 1;
    if (af_fmt_is_planar(ab->format)) {
        ab->num_planes = ab->channels.num;
    } else {
        ab->sstride *= ab->channels.num;
    }
}