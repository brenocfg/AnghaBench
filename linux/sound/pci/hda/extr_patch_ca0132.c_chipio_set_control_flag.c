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
typedef  enum control_flag_id { ____Placeholder_control_flag_id } control_flag_id ;

/* Variables and functions */
 int /*<<< orphan*/  VENDOR_CHIPIO_FLAG_SET ; 
 int /*<<< orphan*/  WIDGET_CHIP_CTRL ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void chipio_set_control_flag(struct hda_codec *codec,
				    enum control_flag_id flag_id,
				    bool flag_state)
{
	unsigned int val;
	unsigned int flag_bit;

	flag_bit = (flag_state ? 1 : 0);
	val = (flag_bit << 7) | (flag_id);
	snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0,
			    VENDOR_CHIPIO_FLAG_SET, val);
}