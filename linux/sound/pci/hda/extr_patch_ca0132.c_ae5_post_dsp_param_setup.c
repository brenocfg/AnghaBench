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
 int /*<<< orphan*/  CONTROL_FLAG_ASI_96KHZ ; 
 int CONTROL_PARAM_ASI ; 
 int VENDOR_CHIPIO_8051_ADDRESS_HIGH ; 
 int VENDOR_CHIPIO_8051_ADDRESS_LOW ; 
 int VENDOR_CHIPIO_8051_DATA_WRITE ; 
 int /*<<< orphan*/  WIDGET_CHIP_CTRL ; 
 int /*<<< orphan*/  chipio_set_control_flag (struct hda_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chipio_set_control_param (struct hda_codec*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void ae5_post_dsp_param_setup(struct hda_codec *codec)
{
	/*
	 * Param3 in the 8051's memory is represented by the ascii string 'mch'
	 * which seems to be 'multichannel'. This is also mentioned in the
	 * AE-5's registry values in Windows.
	 */
	chipio_set_control_param(codec, 3, 0);
	/*
	 * I believe ASI is 'audio serial interface' and that it's used to
	 * change colors on the external LED strip connected to the AE-5.
	 */
	chipio_set_control_flag(codec, CONTROL_FLAG_ASI_96KHZ, 1);

	snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0, 0x724, 0x83);
	chipio_set_control_param(codec, CONTROL_PARAM_ASI, 0);

	snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_8051_ADDRESS_LOW, 0x92);
	snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_8051_ADDRESS_HIGH, 0xfa);
	snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_8051_DATA_WRITE, 0x22);
}