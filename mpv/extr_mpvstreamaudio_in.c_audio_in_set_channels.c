#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int type; } ;
typedef  TYPE_1__ audio_in_t ;

/* Variables and functions */

int audio_in_set_channels(audio_in_t *ai, int channels)
{
    switch (ai->type) {
#if HAVE_ALSA
    case AUDIO_IN_ALSA:
        ai->req_channels = channels;
        if (!ai->setup) return 0;
        if (ai_alsa_setup(ai) < 0) return -1;
        return ai->channels;
#endif
#if HAVE_OSS_AUDIO
    case AUDIO_IN_OSS:
        ai->req_channels = channels;
        if (!ai->setup) return 0;
        if (ai_oss_set_channels(ai) < 0) return -1;
        return ai->channels;
#endif
#if HAVE_SNDIO
    case AUDIO_IN_SNDIO:
       ai->req_channels = channels;
       if (!ai->setup) return 0;
       if (ai_sndio_setup(ai) < 0) return -1;
       return ai->channels;
#endif
    default:
        return -1;
    }
}