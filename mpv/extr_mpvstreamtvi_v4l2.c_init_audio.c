#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ audmode; } ;
struct TYPE_6__ {int capabilities; } ;
struct TYPE_9__ {int audio_initialized; int /*<<< orphan*/  audio_in; TYPE_3__* tv_param; TYPE_2__ tuner; TYPE_1__ capability; scalar_t__ audio_dev; int /*<<< orphan*/  log; } ;
typedef  TYPE_4__ priv_t ;
struct TYPE_8__ {int forcechan; scalar_t__ audio; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_IN_OSS ; 
 int V4L2_CAP_TUNER ; 
 scalar_t__ V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  audio_in_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_in_set_channels (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  audio_in_set_device (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  audio_in_set_samplerate (int /*<<< orphan*/ *,int) ; 
 scalar_t__ audio_in_setup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_audio(priv_t *priv)
{
    if (priv->audio_initialized) return;

    if (priv->tv_param->audio) {
#if HAVE_ALSA
        if (priv->tv_param->alsa)
            audio_in_init(&priv->audio_in, priv->log, AUDIO_IN_ALSA);
        else
            audio_in_init(&priv->audio_in, priv->log, AUDIO_IN_OSS);
#else
        audio_in_init(&priv->audio_in, priv->log, AUDIO_IN_OSS);
#endif

        if (priv->audio_dev) {
            audio_in_set_device(&priv->audio_in, priv->audio_dev);
        }

        audio_in_set_samplerate(&priv->audio_in, 44100);
        if (priv->capability.capabilities & V4L2_CAP_TUNER) {
            if (priv->tuner.audmode == V4L2_TUNER_MODE_STEREO) {
                audio_in_set_channels(&priv->audio_in, 2);
            } else {
                audio_in_set_channels(&priv->audio_in, 1);
            }
        } else {
            if (priv->tv_param->forcechan >= 0) {
                audio_in_set_channels(&priv->audio_in, priv->tv_param->forcechan);
            } else {
                audio_in_set_channels(&priv->audio_in, 2);
            }
        }

        if (audio_in_setup(&priv->audio_in) < 0) return;

        priv->audio_initialized = 1;
    }
}