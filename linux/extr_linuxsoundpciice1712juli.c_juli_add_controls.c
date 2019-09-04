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
struct snd_kcontrol {int dummy; } ;
struct snd_ice1712 {TYPE_2__* pcm; int /*<<< orphan*/  card; struct juli_spec* spec; } ;
struct juli_spec {int /*<<< orphan*/  ak4114; } ;
struct TYPE_4__ {TYPE_1__* streams; } ;
struct TYPE_3__ {int /*<<< orphan*/  substream; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  add_slaves (int /*<<< orphan*/ ,struct snd_kcontrol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  juli_master_db_scale ; 
 int /*<<< orphan*/ * juli_mute_controls ; 
 int /*<<< orphan*/  slave_vols ; 
 int snd_ak4114_build (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_ctl_add (int /*<<< orphan*/ ,struct snd_kcontrol*) ; 
 struct snd_kcontrol* snd_ctl_make_virtual_master (char*,int /*<<< orphan*/ ) ; 
 struct snd_kcontrol* snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_ice1712*) ; 
 int snd_ice1712_akm4xxx_build_controls (struct snd_ice1712*) ; 

__attribute__((used)) static int juli_add_controls(struct snd_ice1712 *ice)
{
	struct juli_spec *spec = ice->spec;
	int err;
	unsigned int i;
	struct snd_kcontrol *vmaster;

	err = snd_ice1712_akm4xxx_build_controls(ice);
	if (err < 0)
		return err;

	for (i = 0; i < ARRAY_SIZE(juli_mute_controls); i++) {
		err = snd_ctl_add(ice->card,
				snd_ctl_new1(&juli_mute_controls[i], ice));
		if (err < 0)
			return err;
	}
	/* Create virtual master control */
	vmaster = snd_ctl_make_virtual_master("Master Playback Volume",
					      juli_master_db_scale);
	if (!vmaster)
		return -ENOMEM;
	add_slaves(ice->card, vmaster, slave_vols);
	err = snd_ctl_add(ice->card, vmaster);
	if (err < 0)
		return err;

	/* only capture SPDIF over AK4114 */
	return snd_ak4114_build(spec->ak4114, NULL,
			ice->pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream);
}