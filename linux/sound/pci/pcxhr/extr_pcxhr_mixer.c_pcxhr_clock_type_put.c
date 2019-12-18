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
struct TYPE_3__ {unsigned int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct pcxhr_mgr {scalar_t__ use_clock_type; int sample_rate; int /*<<< orphan*/  mixer_mutex; int /*<<< orphan*/  setup_mutex; int /*<<< orphan*/  is_hr_stereo; scalar_t__ capture_chips; scalar_t__ board_has_aes1; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PCXHR_CLOCK_TYPE_INTERNAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcxhr_get_external_clock (struct pcxhr_mgr*,scalar_t__,int*) ; 
 int /*<<< orphan*/  pcxhr_set_clock (struct pcxhr_mgr*,int) ; 
 struct pcxhr_mgr* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int pcxhr_clock_type_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct pcxhr_mgr *mgr = snd_kcontrol_chip(kcontrol);
	int rate, ret = 0;
	unsigned int clock_items = 2; /* at least Internal and AES Sync clock */
	if (mgr->board_has_aes1) {
		clock_items += mgr->capture_chips;	/* add AES x */
		if (!mgr->is_hr_stereo)
			clock_items += 1;		/* add word clock */
	}
	if (ucontrol->value.enumerated.item[0] >= clock_items)
		return -EINVAL;
	mutex_lock(&mgr->mixer_mutex);
	if (mgr->use_clock_type != ucontrol->value.enumerated.item[0]) {
		mutex_lock(&mgr->setup_mutex);
		mgr->use_clock_type = ucontrol->value.enumerated.item[0];
		rate = 0;
		if (mgr->use_clock_type != PCXHR_CLOCK_TYPE_INTERNAL) {
			pcxhr_get_external_clock(mgr, mgr->use_clock_type,
						 &rate);
		} else {
			rate = mgr->sample_rate;
			if (!rate)
				rate = 48000;
		}
		if (rate) {
			pcxhr_set_clock(mgr, rate);
			if (mgr->sample_rate)
				mgr->sample_rate = rate;
		}
		mutex_unlock(&mgr->setup_mutex);
		ret = 1; /* return 1 even if the set was not done. ok ? */
	}
	mutex_unlock(&mgr->mixer_mutex);
	return ret;
}