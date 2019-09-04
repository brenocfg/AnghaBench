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
struct mp_log {int dummy; } ;
struct TYPE_3__ {int type; int channels; int samplerate; int blocksize; int bytes_per_sample; int samplesize; struct mp_log* log; scalar_t__ setup; } ;
typedef  TYPE_1__ audio_in_t ;

/* Variables and functions */

int audio_in_init(audio_in_t *ai, struct mp_log *log, int type)
{
    ai->type = type;
    ai->setup = 0;
    ai->log = log;

    ai->channels = -1;
    ai->samplerate = -1;
    ai->blocksize = -1;
    ai->bytes_per_sample = -1;
    ai->samplesize = -1;

    switch (ai->type) {
#if HAVE_ALSA
    case AUDIO_IN_ALSA:
        ai->alsa.handle = NULL;
        ai->alsa.log = NULL;
        ai->alsa.device = NULL;
        return 0;
#endif
#if HAVE_OSS_AUDIO
    case AUDIO_IN_OSS:
        ai->oss.audio_fd = -1;
        ai->oss.device = NULL;
        return 0;
#endif
#if HAVE_SNDIO
    case AUDIO_IN_SNDIO:
        ai->sndio.hdl = NULL;
        ai->sndio.device = NULL;
        return 0;
#endif
    default:
        return -1;
    }
}