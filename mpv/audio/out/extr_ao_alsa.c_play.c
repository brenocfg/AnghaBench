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
struct priv {int outburst; int paused; int final_chunk_written; int /*<<< orphan*/  alsa; int /*<<< orphan*/  convert; } ;
struct ao {int /*<<< orphan*/  format; struct priv* priv; } ;
typedef  int snd_pcm_sframes_t ;

/* Variables and functions */
 int AOPLAY_FINAL_CHUNK ; 
 int /*<<< orphan*/  CHECK_ALSA_ERROR (char*) ; 
 int EAGAIN ; 
 int EINTR ; 
 int EPIPE ; 
 int ESTRPIPE ; 
 int /*<<< orphan*/  MP_ERR (struct ao*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ af_fmt_is_planar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ao_convert_inplace (int /*<<< orphan*/ *,void**,int) ; 
 int /*<<< orphan*/  check_device_present (struct ao*,int) ; 
 int /*<<< orphan*/  handle_underrun (struct ao*) ; 
 int /*<<< orphan*/  resume_device (struct ao*) ; 
 int snd_pcm_prepare (int /*<<< orphan*/ ) ; 
 int snd_pcm_writei (int /*<<< orphan*/ ,void*,int) ; 
 int snd_pcm_writen (int /*<<< orphan*/ ,void**,int) ; 
 int /*<<< orphan*/  snd_strerror (int) ; 

__attribute__((used)) static int play(struct ao *ao, void **data, int samples, int flags)
{
    struct priv *p = ao->priv;
    snd_pcm_sframes_t res = 0;
    bool final_chunk = flags & AOPLAY_FINAL_CHUNK;

    if (!final_chunk)
        samples = samples / p->outburst * p->outburst;

    if (samples == 0)
        goto done;
    ao_convert_inplace(&p->convert, data, samples);

    do {
        if (af_fmt_is_planar(ao->format)) {
            res = snd_pcm_writen(p->alsa, data, samples);
        } else {
            res = snd_pcm_writei(p->alsa, data[0], samples);
        }

        if (res == -EINTR || res == -EAGAIN) { /* retry */
            res = 0;
        } else if (!check_device_present(ao, res)) {
            goto alsa_error;
        } else if (res < 0) {
            if (res == -ESTRPIPE) {  /* suspend */
                resume_device(ao);
            } else if (res == -EPIPE) {
                handle_underrun(ao);
            } else {
                MP_ERR(ao, "Write error: %s\n", snd_strerror(res));
            }
            int err = snd_pcm_prepare(p->alsa);
            CHECK_ALSA_ERROR("pcm prepare error");
            res = 0;
        }
    } while (res == 0);

    p->paused = false;

done:
    p->final_chunk_written = res == samples && final_chunk;
    return res < 0 ? -1 : res;

alsa_error:
    return -1;
}