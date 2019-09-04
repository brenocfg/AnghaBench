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
struct hda_codec {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 unsigned int AC_UNSOL_RES_CP_READY ; 
 unsigned int AC_UNSOL_RES_CP_STATE ; 
 unsigned int AC_UNSOL_RES_SUBTAG ; 
 unsigned int AC_UNSOL_RES_SUBTAG_SHIFT ; 
 unsigned int AC_UNSOL_RES_TAG_SHIFT ; 
 int /*<<< orphan*/  codec_info (struct hda_codec*,char*,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void hdmi_non_intrinsic_event(struct hda_codec *codec, unsigned int res)
{
	int tag = res >> AC_UNSOL_RES_TAG_SHIFT;
	int subtag = (res & AC_UNSOL_RES_SUBTAG) >> AC_UNSOL_RES_SUBTAG_SHIFT;
	int cp_state = !!(res & AC_UNSOL_RES_CP_STATE);
	int cp_ready = !!(res & AC_UNSOL_RES_CP_READY);

	codec_info(codec,
		"HDMI CP event: CODEC=%d TAG=%d SUBTAG=0x%x CP_STATE=%d CP_READY=%d\n",
		codec->addr,
		tag,
		subtag,
		cp_state,
		cp_ready);

	/* TODO */
	if (cp_state)
		;
	if (cp_ready)
		;
}