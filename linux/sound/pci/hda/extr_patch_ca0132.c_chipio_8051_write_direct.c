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
 unsigned int VENDOR_CHIPIO_8051_WRITE_DIRECT ; 
 int /*<<< orphan*/  WIDGET_CHIP_CTRL ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void chipio_8051_write_direct(struct hda_codec *codec,
		unsigned int addr, unsigned int data)
{
	unsigned int verb;

	verb = VENDOR_CHIPIO_8051_WRITE_DIRECT | data;
	snd_hda_codec_write(codec, WIDGET_CHIP_CTRL, 0, verb, addr);
}