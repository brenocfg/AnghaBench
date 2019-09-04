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
 unsigned int FLOAT_THREE ; 
 int /*<<< orphan*/  MEM_CONNID_MICIN1 ; 
 int /*<<< orphan*/  MEM_CONNID_MICOUT1 ; 
 int /*<<< orphan*/  SR_96_000 ; 
 int /*<<< orphan*/  chipio_set_conn_rate (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chipio_set_stream_control (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  chipio_write (struct hda_codec*,int,int) ; 
 int /*<<< orphan*/  dspio_set_uint_param (struct hda_codec*,int,int,unsigned int) ; 

__attribute__((used)) static void sbz_dsp_initial_mic_setup(struct hda_codec *codec)
{
	unsigned int tmp;

	chipio_set_stream_control(codec, 0x03, 0);
	chipio_set_stream_control(codec, 0x04, 0);

	chipio_set_conn_rate(codec, MEM_CONNID_MICIN1, SR_96_000);
	chipio_set_conn_rate(codec, MEM_CONNID_MICOUT1, SR_96_000);

	tmp = FLOAT_THREE;
	dspio_set_uint_param(codec, 0x80, 0x00, tmp);

	chipio_set_stream_control(codec, 0x03, 1);
	chipio_set_stream_control(codec, 0x04, 1);

	chipio_write(codec, 0x18b098, 0x0000000c);
	chipio_write(codec, 0x18b09C, 0x0000000c);
}