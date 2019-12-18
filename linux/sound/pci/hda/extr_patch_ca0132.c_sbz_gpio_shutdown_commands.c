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
 int /*<<< orphan*/  AC_VERB_SET_GPIO_DATA ; 
 int /*<<< orphan*/  AC_VERB_SET_GPIO_DIRECTION ; 
 int /*<<< orphan*/  AC_VERB_SET_GPIO_MASK ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sbz_gpio_shutdown_commands(struct hda_codec *codec, int dir,
							int mask, int data)
{
	if (dir >= 0)
		snd_hda_codec_write(codec, 0x01, 0,
				AC_VERB_SET_GPIO_DIRECTION, dir);
	if (mask >= 0)
		snd_hda_codec_write(codec, 0x01, 0,
				AC_VERB_SET_GPIO_MASK, mask);

	if (data >= 0)
		snd_hda_codec_write(codec, 0x01, 0,
				AC_VERB_SET_GPIO_DATA, data);
}