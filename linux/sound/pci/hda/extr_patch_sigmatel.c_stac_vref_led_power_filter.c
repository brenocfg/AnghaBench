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
struct TYPE_2__ {scalar_t__ afg; } ;
struct hda_codec {TYPE_1__ core; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 unsigned int AC_PWRST_D1 ; 
 unsigned int AC_PWRST_D3 ; 
 unsigned int snd_hda_gen_path_power_filter (struct hda_codec*,scalar_t__,unsigned int) ; 

__attribute__((used)) static unsigned int stac_vref_led_power_filter(struct hda_codec *codec,
					       hda_nid_t nid,
					       unsigned int power_state)
{
	if (nid == codec->core.afg && power_state == AC_PWRST_D3)
		return AC_PWRST_D1;
	return snd_hda_gen_path_power_filter(codec, nid, power_state);
}