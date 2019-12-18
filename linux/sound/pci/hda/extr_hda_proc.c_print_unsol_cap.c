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
struct snd_info_buffer {int dummy; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int AC_UNSOL_ENABLED ; 
 int AC_UNSOL_TAG ; 
 int /*<<< orphan*/  AC_VERB_GET_UNSOLICITED_RESPONSE ; 
 int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,int,int) ; 

__attribute__((used)) static void print_unsol_cap(struct snd_info_buffer *buffer,
			      struct hda_codec *codec, hda_nid_t nid)
{
	int unsol = snd_hda_codec_read(codec, nid, 0,
				       AC_VERB_GET_UNSOLICITED_RESPONSE, 0);
	snd_iprintf(buffer,
		    "  Unsolicited: tag=%02x, enabled=%d\n",
		    unsol & AC_UNSOL_TAG,
		    (unsol & AC_UNSOL_ENABLED) ? 1 : 0);
}