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
struct priv {int buffersize; int outburst; int /*<<< orphan*/  alsa; scalar_t__ paused; } ;
struct ao {struct priv* priv; } ;
typedef  int snd_pcm_sframes_t ;

/* Variables and functions */
 int EPIPE ; 
 int /*<<< orphan*/  MP_ERR (struct ao*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SND_PCM_STATE_SETUP ; 
 int /*<<< orphan*/  check_device_present (struct ao*,int) ; 
 int /*<<< orphan*/  handle_underrun (struct ao*) ; 
 int snd_pcm_avail (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_state_name (scalar_t__) ; 
 int /*<<< orphan*/  snd_strerror (int) ; 

__attribute__((used)) static int get_space(struct ao *ao)
{
    struct priv *p = ao->priv;

    // in case of pausing or the device still being configured,
    // just return our buffer size.
    if (p->paused || snd_pcm_state(p->alsa) == SND_PCM_STATE_SETUP)
        return p->buffersize;

    snd_pcm_sframes_t space = snd_pcm_avail(p->alsa);
    if (space < 0 && space != -EPIPE) {
        MP_ERR(ao, "Error received from snd_pcm_avail "
                   "(%ld, %s with ALSA state %s)!\n",
               space, snd_strerror(space),
               snd_pcm_state_name(snd_pcm_state(p->alsa)));

        // request a reload of the AO if device is not present,
        // then error out.
        check_device_present(ao, space);
        goto alsa_error;
    }
    if (space == -EPIPE)
        handle_underrun(ao);

    if (space > p->buffersize || space < 0) // Buffer underrun?
        space = p->buffersize;
    return space / p->outburst * p->outburst;

alsa_error:
    return 0;
}