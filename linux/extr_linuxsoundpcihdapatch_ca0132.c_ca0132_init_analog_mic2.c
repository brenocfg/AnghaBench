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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {int /*<<< orphan*/  chipio_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  VENDOR_CHIPIO_8051_ADDRESS_HIGH ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_8051_ADDRESS_LOW ; 
 int /*<<< orphan*/  VENDOR_CHIPIO_8051_DATA_WRITE ; 
 int /*<<< orphan*/  WIDGET_CHIP_CTRL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ca0132_init_analog_mic2(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;

	mutex_lock(&spec->chipio_mutex);
	snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_8051_ADDRESS_LOW, 0x20);
	snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_8051_ADDRESS_HIGH, 0x19);
	snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_8051_DATA_WRITE, 0x00);
	snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_8051_ADDRESS_LOW, 0x2D);
	snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_8051_ADDRESS_HIGH, 0x19);
	snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_8051_DATA_WRITE, 0x00);
	mutex_unlock(&spec->chipio_mutex);
}