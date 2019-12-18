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
typedef  int hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_POWER_STATE ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zxr_dbpro_power_state_shutdown(struct hda_codec *codec)
{
	hda_nid_t pins[7] = {0x05, 0x0c, 0x09, 0x0e, 0x08, 0x11, 0x01};
	unsigned int i;

	for (i = 0; i < 7; i++)
		snd_hda_codec_write(codec, pins[i], 0,
				AC_VERB_SET_POWER_STATE, 0x03);
}