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
typedef  int u32 ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct hdspm {int dummy; } ;

/* Variables and functions */
 scalar_t__ HDSPM_RD_TCO ; 
#define  HDSPM_TCO1_Video_Input_Format_NTSC 129 
#define  HDSPM_TCO1_Video_Input_Format_PAL 128 
 int hdspm_read (struct hdspm*,scalar_t__) ; 
 struct hdspm* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_hdspm_get_tco_video_input_format(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_value *ucontrol)
{
	u32 status;
	int ret = 0;

	struct hdspm *hdspm = snd_kcontrol_chip(kcontrol);
	status = hdspm_read(hdspm, HDSPM_RD_TCO + 4);
	switch (status & (HDSPM_TCO1_Video_Input_Format_NTSC |
			HDSPM_TCO1_Video_Input_Format_PAL)) {
	case HDSPM_TCO1_Video_Input_Format_NTSC:
		/* ntsc */
		ret = 1;
		break;
	case HDSPM_TCO1_Video_Input_Format_PAL:
		/* pal */
		ret = 2;
		break;
	default:
		/* no video */
		ret = 0;
		break;
	}
	ucontrol->value.enumerated.item[0] = ret;
	return 0;
}