#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct priv {TYPE_1__* opts; } ;
struct mp_chmap {int num; } ;
struct ao {struct mp_chmap channels; int /*<<< orphan*/  format; int /*<<< orphan*/  global; struct priv* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  ni; } ;

/* Variables and functions */
 int INIT_DEVICE_ERR_HWPARAMS ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,...) ; 
 int /*<<< orphan*/  MP_WARN (struct ao*,char*) ; 
 int SND_PCM_NO_AUTO_CHANNELS ; 
 int SND_PCM_NO_AUTO_FORMAT ; 
 int SND_PCM_NO_AUTO_RESAMPLE ; 
 int /*<<< orphan*/  af_fmt_from_planar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ao_alsa_conf ; 
 int init_device (struct ao*,int) ; 
 scalar_t__ mp_chmap_is_valid (struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_remove_na (struct mp_chmap*) ; 
 TYPE_1__* mp_get_config_group (struct ao*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_asoundlib_version () ; 
 int /*<<< orphan*/  uninit (struct ao*) ; 

__attribute__((used)) static int init(struct ao *ao)
{
    struct priv *p = ao->priv;
    p->opts = mp_get_config_group(ao, ao->global, &ao_alsa_conf);

    if (!p->opts->ni)
        ao->format = af_fmt_from_planar(ao->format);

    MP_VERBOSE(ao, "using ALSA version: %s\n", snd_asoundlib_version());

    int mode = 0;
    int r = init_device(ao, mode);
    if (r == INIT_DEVICE_ERR_HWPARAMS) {
        // With some drivers, ALSA appears to be unable to set valid hwparams,
        // but they work if at least SND_PCM_NO_AUTO_FORMAT is set. Also, it
        // appears you can set this flag only on opening a device, thus there
        // is the need to retry opening the device.
        MP_WARN(ao, "Attempting to work around even more ALSA bugs...\n");
        mode |= SND_PCM_NO_AUTO_CHANNELS | SND_PCM_NO_AUTO_FORMAT |
                SND_PCM_NO_AUTO_RESAMPLE;
        r = init_device(ao, mode);
    }

    // Sometimes, ALSA will advertise certain chmaps, but it's not possible to
    // set them. This can happen with dmix: as of alsa 1.0.29, dmix can do
    // stereo only, but advertises the surround chmaps of the underlying device.
    // In this case, e.g. setting 6 channels will succeed, but requesting  5.1
    // afterwards will fail. Then it will return something like "FL FR NA NA NA NA"
    // as channel map. This means we would have to pad stereo output to 6
    // channels with silence, which would require lots of extra processing. You
    // can't change the number of channels to 2 either, because the hw params
    // are already set! So just fuck it and reopen the device with the chmap
    // "cleaned out" of NA entries.
    if (r >= 0) {
        struct mp_chmap without_na = ao->channels;
        mp_chmap_remove_na(&without_na);

        if (mp_chmap_is_valid(&without_na) && without_na.num <= 2 &&
            ao->channels.num > 2)
        {
            MP_VERBOSE(ao, "Working around braindead dmix multichannel behavior.\n");
            uninit(ao);
            ao->channels = without_na;
            r = init_device(ao, mode);
        }
    }

    return r;
}