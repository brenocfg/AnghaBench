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
 int /*<<< orphan*/  CONTROL_PARAM_ASI ; 
 int /*<<< orphan*/  ca0113_mmio_command_set (struct hda_codec*,int,int,int) ; 
 int /*<<< orphan*/  ca0113_mmio_gpio_set (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  chipio_set_control_param (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipio_set_stream_control (struct hda_codec*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void ae5_exit_chip(struct hda_codec *codec)
{
	chipio_set_stream_control(codec, 0x03, 0);
	chipio_set_stream_control(codec, 0x04, 0);

	ca0113_mmio_command_set(codec, 0x30, 0x32, 0x3f);
	ca0113_mmio_command_set(codec, 0x48, 0x07, 0x83);
	ca0113_mmio_command_set(codec, 0x48, 0x07, 0x83);
	ca0113_mmio_command_set(codec, 0x30, 0x30, 0x00);
	ca0113_mmio_command_set(codec, 0x30, 0x2b, 0x00);
	ca0113_mmio_command_set(codec, 0x30, 0x2d, 0x00);
	ca0113_mmio_gpio_set(codec, 0, false);
	ca0113_mmio_gpio_set(codec, 1, false);

	snd_hda_codec_write(codec, 0x01, 0, 0x793, 0x00);
	snd_hda_codec_write(codec, 0x01, 0, 0x794, 0x53);

	chipio_set_control_param(codec, CONTROL_PARAM_ASI, 0);

	chipio_set_stream_control(codec, 0x18, 0);
	chipio_set_stream_control(codec, 0x0c, 0);

	snd_hda_codec_write(codec, 0x01, 0, 0x724, 0x83);
}