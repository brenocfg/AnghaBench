#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; double tv_usec; } ;
typedef  int /*<<< orphan*/  snd_pcm_status_t ;
struct TYPE_5__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  log; } ;
struct TYPE_6__ {TYPE_1__ alsa; int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ audio_in_t ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  MSGL_V ; 
 scalar_t__ SND_PCM_STATE_XRUN ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ ) ; 
 scalar_t__ mp_msg_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_pcm_prepare (int /*<<< orphan*/ ) ; 
 int snd_pcm_status (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_status_alloca (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  snd_pcm_status_dump (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_status_get_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_status_get_trigger_tstamp (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  snd_strerror (int) ; 
 int /*<<< orphan*/  timersub (struct timeval*,struct timeval*,struct timeval*) ; 

int ai_alsa_xrun(audio_in_t *ai)
{
    snd_pcm_status_t *status;
    int res;

    snd_pcm_status_alloca(&status);
    if ((res = snd_pcm_status(ai->alsa.handle, status))<0) {
        MP_ERR(ai, "ALSA status error: %s", snd_strerror(res));
        return -1;
    }
    if (snd_pcm_status_get_state(status) == SND_PCM_STATE_XRUN) {
        struct timeval now, diff, tstamp;
        gettimeofday(&now, 0);
        snd_pcm_status_get_trigger_tstamp(status, &tstamp);
        timersub(&now, &tstamp, &diff);
        MP_ERR(ai, "ALSA xrun!!! (at least %.3f ms long)\n",
               diff.tv_sec * 1000 + diff.tv_usec / 1000.0);
        if (mp_msg_test(ai->log, MSGL_V)) {
            MP_ERR(ai, "ALSA Status:\n");
            snd_pcm_status_dump(status, ai->alsa.log);
        }
        if ((res = snd_pcm_prepare(ai->alsa.handle))<0) {
            MP_ERR(ai, "ALSA xrun: prepare error: %s", snd_strerror(res));
            return -1;
        }
        return 0;               /* ok, data should be accepted again */
    }
    MP_ERR(ai, "ALSA read/write error");
    return -1;
}