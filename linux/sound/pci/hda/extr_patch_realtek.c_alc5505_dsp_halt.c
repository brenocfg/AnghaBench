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
 unsigned int alc5505_coef_get (struct hda_codec*,int) ; 
 int /*<<< orphan*/  alc5505_coef_set (struct hda_codec*,int,unsigned int) ; 

__attribute__((used)) static void alc5505_dsp_halt(struct hda_codec *codec)
{
	unsigned int val;

	alc5505_coef_set(codec, 0x3000, 0x000c); /* DSP CPU stop */
	alc5505_coef_set(codec, 0x880c, 0x0008); /* DDR enter self refresh */
	alc5505_coef_set(codec, 0x61c0, 0x11110080); /* Clock control for PLL and CPU */
	alc5505_coef_set(codec, 0x6230, 0xfc0d4011); /* Disable Input OP */
	alc5505_coef_set(codec, 0x61b4, 0x040a2b03); /* Stop PLL2 */
	alc5505_coef_set(codec, 0x61b0, 0x00005b17); /* Stop PLL1 */
	alc5505_coef_set(codec, 0x61b8, 0x04133303); /* Stop PLL3 */
	val = alc5505_coef_get(codec, 0x6220);
	alc5505_coef_set(codec, 0x6220, (val | 0x3000)); /* switch Ringbuffer clock to DBUS clock */
}