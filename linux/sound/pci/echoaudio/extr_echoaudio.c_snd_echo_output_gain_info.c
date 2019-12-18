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
struct TYPE_3__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_info {TYPE_2__ value; int /*<<< orphan*/  count; int /*<<< orphan*/  type; } ;
struct echoaudio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHOGAIN_MAXOUT ; 
 int /*<<< orphan*/  ECHOGAIN_MINOUT ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
 int /*<<< orphan*/  num_busses_out (struct echoaudio*) ; 
 struct echoaudio* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_echo_output_gain_info(struct snd_kcontrol *kcontrol,
				     struct snd_ctl_elem_info *uinfo)
{
	struct echoaudio *chip;

	chip = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = num_busses_out(chip);
	uinfo->value.integer.min = ECHOGAIN_MINOUT;
	uinfo->value.integer.max = ECHOGAIN_MAXOUT;
	return 0;
}