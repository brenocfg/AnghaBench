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
 unsigned int FLOAT_ZERO ; 
 int /*<<< orphan*/  MEM_CONNID_MICIN1 ; 
 int /*<<< orphan*/  MEM_CONNID_MICIN2 ; 
 int /*<<< orphan*/  MEM_CONNID_MICOUT1 ; 
 int /*<<< orphan*/  MEM_CONNID_MICOUT2 ; 
 int /*<<< orphan*/  SR_96_000 ; 
 int /*<<< orphan*/  chipio_set_conn_rate (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dspio_set_uint_param (struct hda_codec*,int,int,unsigned int) ; 

__attribute__((used)) static void sbz_init_analog_mics(struct hda_codec *codec)
{
	unsigned int tmp;

	/* Mic 1 Setup */
	chipio_set_conn_rate(codec, MEM_CONNID_MICIN1, SR_96_000);
	chipio_set_conn_rate(codec, MEM_CONNID_MICOUT1, SR_96_000);
	tmp = FLOAT_THREE;
	dspio_set_uint_param(codec, 0x80, 0x00, tmp);

	/* Mic 2 Setup, even though it isn't connected on SBZ */
	chipio_set_conn_rate(codec, MEM_CONNID_MICIN2, SR_96_000);
	chipio_set_conn_rate(codec, MEM_CONNID_MICOUT2, SR_96_000);
	tmp = FLOAT_ZERO;
	dspio_set_uint_param(codec, 0x80, 0x01, tmp);

}