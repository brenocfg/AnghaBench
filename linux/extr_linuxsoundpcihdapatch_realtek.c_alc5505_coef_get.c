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
 int /*<<< orphan*/  AC_VERB_GET_PROC_COEF ; 
 int /*<<< orphan*/  AC_VERB_SET_COEF_INDEX ; 
 int snd_hda_codec_read (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int alc5505_coef_get(struct hda_codec *codec, unsigned int index_reg)
{
	unsigned int val;

	snd_hda_codec_write(codec, 0x51, 0, AC_VERB_SET_COEF_INDEX, index_reg >> 1);
	val = snd_hda_codec_read(codec, 0x51, 0, AC_VERB_GET_PROC_COEF, 0)
		& 0xffff;
	val |= snd_hda_codec_read(codec, 0x51, 0, AC_VERB_GET_PROC_COEF, 0)
		<< 16;
	return val;
}