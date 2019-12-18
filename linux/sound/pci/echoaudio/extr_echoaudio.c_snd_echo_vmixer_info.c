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
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * d; } ;
struct TYPE_5__ {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_info {int count; TYPE_1__ dimen; TYPE_3__ value; int /*<<< orphan*/  type; } ;
struct echoaudio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECHOGAIN_MAXOUT ; 
 int /*<<< orphan*/  ECHOGAIN_MINOUT ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_TYPE_INTEGER ; 
 int /*<<< orphan*/  num_busses_out (struct echoaudio*) ; 
 int /*<<< orphan*/  num_pipes_out (struct echoaudio*) ; 
 struct echoaudio* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_echo_vmixer_info(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_info *uinfo)
{
	struct echoaudio *chip;

	chip = snd_kcontrol_chip(kcontrol);
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.integer.min = ECHOGAIN_MINOUT;
	uinfo->value.integer.max = ECHOGAIN_MAXOUT;
	uinfo->dimen.d[0] = num_busses_out(chip);
	uinfo->dimen.d[1] = num_pipes_out(chip);
	return 0;
}