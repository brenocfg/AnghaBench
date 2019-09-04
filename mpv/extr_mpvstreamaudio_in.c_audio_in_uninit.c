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
struct TYPE_3__ {int type; scalar_t__ setup; } ;
typedef  TYPE_1__ audio_in_t ;

/* Variables and functions */

int audio_in_uninit(audio_in_t *ai)
{
    if (ai->setup) {
        switch (ai->type) {
#if HAVE_ALSA
        case AUDIO_IN_ALSA:
            if (ai->alsa.log)
                snd_output_close(ai->alsa.log);
            if (ai->alsa.handle) {
                snd_pcm_close(ai->alsa.handle);
            }
            ai->setup = 0;
            return 0;
#endif
#if HAVE_OSS_AUDIO
        case AUDIO_IN_OSS:
            close(ai->oss.audio_fd);
            ai->setup = 0;
            return 0;
#endif
#if HAVE_SNDIO
       case AUDIO_IN_SNDIO:
           if (ai->sndio.hdl)
               sio_close(ai->sndio.hdl);
           ai->setup = 0;
           return 0;
#endif
        }
    }
    return -1;
}