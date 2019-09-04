#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct priv {TYPE_1__* opts; } ;
struct ao {int /*<<< orphan*/  format; struct priv* priv; } ;
typedef  int /*<<< orphan*/  snd_mixer_t ;
typedef  int /*<<< orphan*/  snd_mixer_selem_id_t ;
typedef  int /*<<< orphan*/  snd_mixer_elem_t ;
typedef  enum aocontrol { ____Placeholder_aocontrol } aocontrol ;
struct TYPE_4__ {float left; float right; } ;
typedef  TYPE_2__ ao_control_vol_t ;
struct TYPE_3__ {int /*<<< orphan*/  mixer_device; int /*<<< orphan*/  mixer_name; int /*<<< orphan*/  mixer_index; } ;

/* Variables and functions */
#define  AOCONTROL_GET_MUTE 131 
#define  AOCONTROL_GET_VOLUME 130 
#define  AOCONTROL_SET_MUTE 129 
#define  AOCONTROL_SET_VOLUME 128 
 int /*<<< orphan*/  CHECK_ALSA_ERROR (char*) ; 
 int CONTROL_ERROR ; 
 int CONTROL_FALSE ; 
 int CONTROL_OK ; 
 int CONTROL_UNKNOWN ; 
 int /*<<< orphan*/  MP_DBG (struct ao*,char*,long,...) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  af_fmt_is_pcm (int /*<<< orphan*/ ) ; 
 int snd_mixer_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mixer_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * snd_mixer_find_selem (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int snd_mixer_load (int /*<<< orphan*/ *) ; 
 int snd_mixer_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mixer_selem_get_playback_switch (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  snd_mixer_selem_get_playback_volume (int /*<<< orphan*/ *,int,long*) ; 
 int /*<<< orphan*/  snd_mixer_selem_get_playback_volume_range (int /*<<< orphan*/ *,long*,long*) ; 
 int /*<<< orphan*/  snd_mixer_selem_has_playback_switch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mixer_selem_has_playback_switch_joined (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mixer_selem_id_alloca (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  snd_mixer_selem_id_get_index (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mixer_selem_id_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mixer_selem_id_set_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mixer_selem_id_set_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_mixer_selem_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_mixer_selem_set_playback_switch (int /*<<< orphan*/ *,int,int) ; 
 int snd_mixer_selem_set_playback_volume (int /*<<< orphan*/ *,int,long) ; 

__attribute__((used)) static int control(struct ao *ao, enum aocontrol cmd, void *arg)
{
    struct priv *p = ao->priv;
    snd_mixer_t *handle = NULL;
    switch (cmd) {
    case AOCONTROL_GET_MUTE:
    case AOCONTROL_SET_MUTE:
    case AOCONTROL_GET_VOLUME:
    case AOCONTROL_SET_VOLUME:
    {
        int err;
        snd_mixer_elem_t *elem;
        snd_mixer_selem_id_t *sid;

        long pmin, pmax;
        long get_vol, set_vol;
        float f_multi;

        if (!af_fmt_is_pcm(ao->format))
            return CONTROL_FALSE;

        snd_mixer_selem_id_alloca(&sid);

        snd_mixer_selem_id_set_index(sid, p->opts->mixer_index);
        snd_mixer_selem_id_set_name(sid, p->opts->mixer_name);

        err = snd_mixer_open(&handle, 0);
        CHECK_ALSA_ERROR("Mixer open error");

        err = snd_mixer_attach(handle, p->opts->mixer_device);
        CHECK_ALSA_ERROR("Mixer attach error");

        err = snd_mixer_selem_register(handle, NULL, NULL);
        CHECK_ALSA_ERROR("Mixer register error");

        err = snd_mixer_load(handle);
        CHECK_ALSA_ERROR("Mixer load error");

        elem = snd_mixer_find_selem(handle, sid);
        if (!elem) {
            MP_VERBOSE(ao, "Unable to find simple control '%s',%i.\n",
                       snd_mixer_selem_id_get_name(sid),
                       snd_mixer_selem_id_get_index(sid));
            goto alsa_error;
        }

        snd_mixer_selem_get_playback_volume_range(elem, &pmin, &pmax);
        f_multi = (100 / (float)(pmax - pmin));

        switch (cmd) {
        case AOCONTROL_SET_VOLUME: {
            ao_control_vol_t *vol = arg;
            set_vol = vol->left / f_multi + pmin + 0.5;

            err = snd_mixer_selem_set_playback_volume(elem, 0, set_vol);
            CHECK_ALSA_ERROR("Error setting left channel");
            MP_DBG(ao, "left=%li, ", set_vol);

            set_vol = vol->right / f_multi + pmin + 0.5;

            err = snd_mixer_selem_set_playback_volume(elem, 1, set_vol);
            CHECK_ALSA_ERROR("Error setting right channel");
            MP_DBG(ao, "right=%li, pmin=%li, pmax=%li, mult=%f\n",
                   set_vol, pmin, pmax, f_multi);
            break;
        }
        case AOCONTROL_GET_VOLUME: {
            ao_control_vol_t *vol = arg;
            snd_mixer_selem_get_playback_volume(elem, 0, &get_vol);
            vol->left = (get_vol - pmin) * f_multi;
            snd_mixer_selem_get_playback_volume(elem, 1, &get_vol);
            vol->right = (get_vol - pmin) * f_multi;
            MP_DBG(ao, "left=%f, right=%f\n", vol->left, vol->right);
            break;
        }
        case AOCONTROL_SET_MUTE: {
            bool *mute = arg;
            if (!snd_mixer_selem_has_playback_switch(elem))
                goto alsa_error;
            if (!snd_mixer_selem_has_playback_switch_joined(elem)) {
                snd_mixer_selem_set_playback_switch(elem, 1, !*mute);
            }
            snd_mixer_selem_set_playback_switch(elem, 0, !*mute);
            break;
        }
        case AOCONTROL_GET_MUTE: {
            bool *mute = arg;
            if (!snd_mixer_selem_has_playback_switch(elem))
                goto alsa_error;
            int tmp = 1;
            snd_mixer_selem_get_playback_switch(elem, 0, &tmp);
            *mute = !tmp;
            if (!snd_mixer_selem_has_playback_switch_joined(elem)) {
                snd_mixer_selem_get_playback_switch(elem, 1, &tmp);
                *mute &= !tmp;
            }
            break;
        }
        }
        snd_mixer_close(handle);
        return CONTROL_OK;
    }

    } //end switch
    return CONTROL_UNKNOWN;

alsa_error:
    if (handle)
        snd_mixer_close(handle);
    return CONTROL_ERROR;
}