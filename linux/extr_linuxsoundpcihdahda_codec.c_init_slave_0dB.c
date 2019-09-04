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
struct TYPE_6__ {scalar_t__ c; int* p; } ;
struct TYPE_4__ {int name; int index; } ;
struct snd_kcontrol {TYPE_3__ tlv; TYPE_2__* vd; TYPE_1__ id; } ;
struct slave_init_arg {int step; int /*<<< orphan*/  codec; } ;
struct TYPE_5__ {int access; } ;

/* Variables and functions */
 int SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK ; 
 int SNDRV_CTL_ELEM_ACCESS_TLV_READ ; 
 size_t SNDRV_CTL_TLVO_DB_SCALE_MIN ; 
 size_t SNDRV_CTL_TLVO_DB_SCALE_MUTE_AND_STEP ; 
 size_t SNDRV_CTL_TLVO_TYPE ; 
 int const SNDRV_CTL_TLVT_DB_SCALE ; 
 int TLV_DB_SCALE_MUTE ; 
 int /*<<< orphan*/  codec_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  get_ctl_amp_tlv (struct snd_kcontrol*,int*) ; 
 int /*<<< orphan*/  put_kctl_with_value (struct snd_kcontrol*,int) ; 
 scalar_t__ snd_hda_mixer_amp_tlv ; 

__attribute__((used)) static int init_slave_0dB(struct snd_kcontrol *slave,
			  struct snd_kcontrol *kctl,
			  void *_arg)
{
	struct slave_init_arg *arg = _arg;
	int _tlv[4];
	const int *tlv = NULL;
	int step;
	int val;

	if (kctl->vd[0].access & SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK) {
		if (kctl->tlv.c != snd_hda_mixer_amp_tlv) {
			codec_err(arg->codec,
				  "Unexpected TLV callback for slave %s:%d\n",
				  kctl->id.name, kctl->id.index);
			return 0; /* ignore */
		}
		get_ctl_amp_tlv(kctl, _tlv);
		tlv = _tlv;
	} else if (kctl->vd[0].access & SNDRV_CTL_ELEM_ACCESS_TLV_READ)
		tlv = kctl->tlv.p;

	if (!tlv || tlv[SNDRV_CTL_TLVO_TYPE] != SNDRV_CTL_TLVT_DB_SCALE)
		return 0;

	step = tlv[SNDRV_CTL_TLVO_DB_SCALE_MUTE_AND_STEP];
	step &= ~TLV_DB_SCALE_MUTE;
	if (!step)
		return 0;
	if (arg->step && arg->step != step) {
		codec_err(arg->codec,
			  "Mismatching dB step for vmaster slave (%d!=%d)\n",
			  arg->step, step);
		return 0;
	}

	arg->step = step;
	val = -tlv[SNDRV_CTL_TLVO_DB_SCALE_MIN] / step;
	if (val > 0) {
		put_kctl_with_value(slave, val);
		return val;
	}

	return 0;
}