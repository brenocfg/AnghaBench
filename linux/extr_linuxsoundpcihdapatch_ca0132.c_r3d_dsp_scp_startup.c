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
 int /*<<< orphan*/  dspio_set_uint_param_no_source (struct hda_codec*,int,int,unsigned int) ; 

__attribute__((used)) static void r3d_dsp_scp_startup(struct hda_codec *codec)
{
	unsigned int tmp;

	tmp = 0x00000000;
	dspio_set_uint_param_no_source(codec, 0x80, 0x0A, tmp);

	tmp = 0x00000001;
	dspio_set_uint_param_no_source(codec, 0x80, 0x0B, tmp);

	tmp = 0x00000004;
	dspio_set_uint_param_no_source(codec, 0x80, 0x0C, tmp);

	tmp = 0x00000005;
	dspio_set_uint_param_no_source(codec, 0x80, 0x0C, tmp);

	tmp = 0x00000000;
	dspio_set_uint_param_no_source(codec, 0x80, 0x0C, tmp);

}