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
 unsigned int FLOAT_ONE ; 
 unsigned int FLOAT_ZERO ; 
 int MEM_CONNID_MICIN1 ; 
 int MEM_CONNID_MICIN2 ; 
 int MEM_CONNID_MICOUT1 ; 
 int MEM_CONNID_MICOUT2 ; 
 int /*<<< orphan*/  SR_96_000 ; 
 int /*<<< orphan*/  chipio_set_conn_rate (struct hda_codec*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dspio_set_uint_param (struct hda_codec*,int,int,unsigned int) ; 

__attribute__((used)) static void r3d_dsp_initial_mic_setup(struct hda_codec *codec)
{
	unsigned int tmp;

	/* Mic 1 Setup */
	chipio_set_conn_rate(codec, MEM_CONNID_MICIN1, SR_96_000);
	chipio_set_conn_rate(codec, MEM_CONNID_MICOUT1, SR_96_000);
	/* This ConnPointID is unique to Recon3Di. Haven't seen it elsewhere */
	chipio_set_conn_rate(codec, 0x0F, SR_96_000);
	tmp = FLOAT_ONE;
	dspio_set_uint_param(codec, 0x80, 0x00, tmp);

	/* Mic 2 Setup, even though it isn't connected on SBZ */
	chipio_set_conn_rate(codec, MEM_CONNID_MICIN2, SR_96_000);
	chipio_set_conn_rate(codec, MEM_CONNID_MICOUT2, SR_96_000);
	chipio_set_conn_rate(codec, 0x0F, SR_96_000);
	tmp = FLOAT_ZERO;
	dspio_set_uint_param(codec, 0x80, 0x01, tmp);
}