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

/* Variables and functions */
 int /*<<< orphan*/  alc5505_coef_set (struct hda_codec*,int,int) ; 

__attribute__((used)) static void alc5505_dsp_back_from_halt(struct hda_codec *codec)
{
	alc5505_coef_set(codec, 0x61b8, 0x04133302);
	alc5505_coef_set(codec, 0x61b0, 0x00005b16);
	alc5505_coef_set(codec, 0x61b4, 0x040a2b02);
	alc5505_coef_set(codec, 0x6230, 0xf80d4011);
	alc5505_coef_set(codec, 0x6220, 0x2002010f);
	alc5505_coef_set(codec, 0x880c, 0x00000004);
}