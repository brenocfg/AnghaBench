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
typedef  int /*<<< orphan*/  tmp ;
struct priv {TYPE_1__* opts; int /*<<< orphan*/  alsa; } ;
struct mp_chmap {int num; } ;
struct ao {struct mp_chmap channels; int /*<<< orphan*/  format; struct priv* priv; } ;
typedef  int /*<<< orphan*/  snd_pcm_chmap_t ;
struct TYPE_2__ {scalar_t__ ignore_chmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_ALSA_WARN (char*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ao*,char*,...) ; 
 int /*<<< orphan*/  MP_WARN (struct ao*,char*) ; 
 scalar_t__ af_fmt_is_spdif (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * map_back_chmap (struct ao*,struct mp_chmap*) ; 
 scalar_t__ mp_chmap_equals (struct mp_chmap*,struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_from_alsa (struct mp_chmap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_chmap_is_valid (struct mp_chmap*) ; 
 int /*<<< orphan*/  mp_chmap_to_str (struct mp_chmap*) ; 
 scalar_t__ snd_pcm_chmap_print (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * snd_pcm_get_chmap (int /*<<< orphan*/ ) ; 
 int snd_pcm_set_chmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_chmap(struct ao *ao, struct mp_chmap *dev_chmap, int num_channels)
{
    struct priv *p = ao->priv;
    int err;

    snd_pcm_chmap_t *alsa_chmap = map_back_chmap(ao, dev_chmap);
    if (alsa_chmap) {
        char tmp[128];
        if (snd_pcm_chmap_print(alsa_chmap, sizeof(tmp), tmp) > 0)
            MP_VERBOSE(ao, "trying to set ALSA channel map: %s\n", tmp);

        err = snd_pcm_set_chmap(p->alsa, alsa_chmap);
        if (err == -ENXIO) {
            // A device my not be able to set any channel map, even channel maps
            // that were reported as supported. This is either because the ALSA
            // device is broken (dmix), or because the driver has only 1
            // channel map per channel count, and setting the map is not needed.
            MP_VERBOSE(ao, "device returned ENXIO when setting channel map %s\n",
                       mp_chmap_to_str(dev_chmap));
        } else {
            CHECK_ALSA_WARN("Channel map setup failed");
        }

        free(alsa_chmap);
    }

    alsa_chmap = snd_pcm_get_chmap(p->alsa);
    if (alsa_chmap) {
        char tmp[128];
        if (snd_pcm_chmap_print(alsa_chmap, sizeof(tmp), tmp) > 0)
            MP_VERBOSE(ao, "channel map reported by ALSA: %s\n", tmp);

        struct mp_chmap chmap;
        mp_chmap_from_alsa(&chmap, alsa_chmap);

        MP_VERBOSE(ao, "which we understand as: %s\n", mp_chmap_to_str(&chmap));

        if (p->opts->ignore_chmap) {
            MP_VERBOSE(ao, "user set ignore-chmap; ignoring the channel map.\n");
        } else if (af_fmt_is_spdif(ao->format)) {
            MP_VERBOSE(ao, "using spdif passthrough; ignoring the channel map.\n");
        } else if (!mp_chmap_is_valid(&chmap)) {
            MP_WARN(ao, "Got unknown channel map from ALSA.\n");
        } else if (chmap.num != num_channels) {
            MP_WARN(ao, "ALSA channel map conflicts with channel count!\n");
        } else {
            if (mp_chmap_equals(&chmap, &ao->channels)) {
                MP_VERBOSE(ao, "which is what we requested.\n");
            } else if (!mp_chmap_is_valid(dev_chmap)) {
                MP_VERBOSE(ao, "ignoring the ALSA channel map.\n");
            } else {
                MP_VERBOSE(ao, "using the ALSA channel map.\n");
                ao->channels = chmap;
            }
        }

        free(alsa_chmap);
    }

    return 0;
}