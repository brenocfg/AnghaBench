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

int audio_in_set_device(audio_in_t *ai, char *device)
{
#if HAVE_ALSA
    int i;
#endif
    if (ai->setup) return -1;
    switch (ai->type) {
#if HAVE_ALSA
    case AUDIO_IN_ALSA:
        free(ai->alsa.device);
        ai->alsa.device = strdup(device);
        if (ai->alsa.device) {
            /* mplayer could not handle colons in arguments */
            for (i = 0; i < (int)strlen(ai->alsa.device); i++) {
                if (ai->alsa.device[i] == '.') ai->alsa.device[i] = ':';
            }
        }
        return 0;
#endif
#if HAVE_OSS_AUDIO
    case AUDIO_IN_OSS:
        free(ai->oss.device);
        ai->oss.device = strdup(device);
        return 0;
#endif
#if HAVE_SNDIO
    case AUDIO_IN_SNDIO:
       if (ai->sndio.device) free(ai->sndio.device);
       ai->sndio.device = strdup(device);
       return 0;
#endif
    default:
        return -1;
    }
}