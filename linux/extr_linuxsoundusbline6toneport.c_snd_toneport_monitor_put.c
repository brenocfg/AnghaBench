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
struct snd_line6_pcm {scalar_t__ volume_monitor; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE6_STREAM_MONITOR ; 
 int line6_pcm_acquire (struct snd_line6_pcm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  line6_pcm_release (struct snd_line6_pcm*,int /*<<< orphan*/ ) ; 
 struct snd_line6_pcm* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_toneport_monitor_put(struct snd_kcontrol *kcontrol,
				    struct snd_ctl_elem_value *ucontrol)
{
	struct snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);
	int err;

	if (ucontrol->value.integer.value[0] == line6pcm->volume_monitor)
		return 0;

	line6pcm->volume_monitor = ucontrol->value.integer.value[0];

	if (line6pcm->volume_monitor > 0) {
		err = line6_pcm_acquire(line6pcm, LINE6_STREAM_MONITOR, true);
		if (err < 0) {
			line6pcm->volume_monitor = 0;
			line6_pcm_release(line6pcm, LINE6_STREAM_MONITOR);
			return err;
		}
	} else {
		line6_pcm_release(line6pcm, LINE6_STREAM_MONITOR);
	}

	return 1;
}