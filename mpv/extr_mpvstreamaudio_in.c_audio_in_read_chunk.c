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

int audio_in_read_chunk(audio_in_t *ai, unsigned char *buffer)
{
    int ret;

    switch (ai->type) {
#if HAVE_ALSA
    case AUDIO_IN_ALSA:
        ret = snd_pcm_readi(ai->alsa.handle, buffer, ai->alsa.chunk_size);
        if (ret != ai->alsa.chunk_size) {
            if (ret < 0) {
                MP_ERR(ai, "\nError reading audio: %s\n", snd_strerror(ret));
                if (ret == -EPIPE) {
                    if (ai_alsa_xrun(ai) == 0) {
                        MP_ERR(ai, "Recovered from cross-run, some frames may be left out!\n");
                    } else {
                        MP_ERR(ai, "Fatal error, cannot recover!\n");
                    }
                }
            } else {
                MP_ERR(ai, "\nNot enough audio samples!\n");
            }
            return -1;
        }
        return ret;
#endif
#if HAVE_OSS_AUDIO
    case AUDIO_IN_OSS:
        ret = read(ai->oss.audio_fd, buffer, ai->blocksize);
       if (ret != ai->blocksize) {
           if (ret < 0) {
               MP_ERR(ai, "\nError reading audio: %s\n", mp_strerror(errno));

           } else {
               MP_ERR(ai, "\nNot enough audio samples!\n");
           }
           return -1;
       }
       return ret;
#endif
#if HAVE_SNDIO
    case AUDIO_IN_SNDIO:
       ret = sio_read(ai->sndio.hdl, buffer, ai->blocksize);
        if (ret != ai->blocksize) {
            if (ret < 0) {
                MP_ERR(ai, "\nError reading audio: %s\n", mp_strerror(errno));
            } else {
                MP_ERR(ai, "\nNot enough audio samples!\n");
            }
            return -1;
        }
        return ret;
#endif
    default:
        return -1;
    }
}