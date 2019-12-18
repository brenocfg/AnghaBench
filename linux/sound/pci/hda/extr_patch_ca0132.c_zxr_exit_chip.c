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
 int AC_VERB_SET_EAPD_BTLENABLE ; 
 int /*<<< orphan*/  SR_192_000 ; 
 int /*<<< orphan*/  ca0113_mmio_gpio_set (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  ca0132_clear_unsolicited (struct hda_codec*) ; 
 int /*<<< orphan*/  chipio_set_conn_rate (struct hda_codec*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipio_set_stream_control (struct hda_codec*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipio_write (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  sbz_set_pin_ctl_default (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void zxr_exit_chip(struct hda_codec *codec)
{
	chipio_set_stream_control(codec, 0x03, 0);
	chipio_set_stream_control(codec, 0x04, 0);
	chipio_set_stream_control(codec, 0x14, 0);
	chipio_set_stream_control(codec, 0x0C, 0);

	chipio_set_conn_rate(codec, 0x41, SR_192_000);
	chipio_set_conn_rate(codec, 0x91, SR_192_000);

	chipio_write(codec, 0x18a020, 0x00000083);

	snd_hda_codec_write(codec, 0x01, 0, 0x793, 0x00);
	snd_hda_codec_write(codec, 0x01, 0, 0x794, 0x53);

	ca0132_clear_unsolicited(codec);
	sbz_set_pin_ctl_default(codec);
	snd_hda_codec_write(codec, 0x0B, 0, AC_VERB_SET_EAPD_BTLENABLE, 0x00);

	ca0113_mmio_gpio_set(codec, 5, false);
	ca0113_mmio_gpio_set(codec, 2, false);
	ca0113_mmio_gpio_set(codec, 3, false);
	ca0113_mmio_gpio_set(codec, 0, false);
	ca0113_mmio_gpio_set(codec, 4, true);
	ca0113_mmio_gpio_set(codec, 0, true);
	ca0113_mmio_gpio_set(codec, 5, true);
	ca0113_mmio_gpio_set(codec, 2, false);
	ca0113_mmio_gpio_set(codec, 3, false);
}