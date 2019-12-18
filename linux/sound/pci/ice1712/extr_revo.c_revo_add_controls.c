#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int subvendor; } ;
struct snd_ice1712 {TYPE_2__* pcm; struct revo51_spec* spec; TYPE_3__ eeprom; } ;
struct revo51_spec {int /*<<< orphan*/  ak4114; int /*<<< orphan*/  pt2258; } ;
struct TYPE_5__ {TYPE_1__* streams; } ;
struct TYPE_4__ {int /*<<< orphan*/  substream; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_CAPTURE ; 
#define  VT1724_SUBDEVICE_AUDIOPHILE192 130 
#define  VT1724_SUBDEVICE_REVOLUTION51 129 
#define  VT1724_SUBDEVICE_REVOLUTION71 128 
 int snd_ak4114_build (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_ice1712_akm4xxx_build_controls (struct snd_ice1712*) ; 
 int snd_pt2258_build_controls (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int revo_add_controls(struct snd_ice1712 *ice)
{
	struct revo51_spec *spec = ice->spec;
	int err;

	switch (ice->eeprom.subvendor) {
	case VT1724_SUBDEVICE_REVOLUTION71:
		err = snd_ice1712_akm4xxx_build_controls(ice);
		if (err < 0)
			return err;
		break;
	case VT1724_SUBDEVICE_REVOLUTION51:
		err = snd_ice1712_akm4xxx_build_controls(ice);
		if (err < 0)
			return err;
		spec = ice->spec;
		err = snd_pt2258_build_controls(spec->pt2258);
		if (err < 0)
			return err;
		break;
	case VT1724_SUBDEVICE_AUDIOPHILE192:
		err = snd_ice1712_akm4xxx_build_controls(ice);
		if (err < 0)
			return err;
		/* only capture SPDIF over AK4114 */
		err = snd_ak4114_build(spec->ak4114, NULL,
		   ice->pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream);
		if (err < 0)
			return err;
		break;
	}
	return 0;
}