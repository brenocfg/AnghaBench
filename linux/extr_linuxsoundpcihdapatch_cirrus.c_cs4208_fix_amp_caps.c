#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_AMPCAP_OFFSET ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 unsigned int query_amp_caps (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_override_amp_caps (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void cs4208_fix_amp_caps(struct hda_codec *codec, hda_nid_t adc)
{
	unsigned int caps;

	caps = query_amp_caps(codec, adc, HDA_INPUT);
	caps &= ~(AC_AMPCAP_OFFSET);
	caps |= 0x02;
	snd_hda_override_amp_caps(codec, adc, HDA_INPUT, caps);
}