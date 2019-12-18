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
 int AC_CONV_CHANNEL ; 
 int AC_CONV_STREAM ; 
 int AC_CONV_STREAM_SHIFT ; 
 int AC_SDI_SELECT ; 
 int /*<<< orphan*/  AC_VERB_GET_CONV ; 
 int /*<<< orphan*/  AC_VERB_GET_SDI_SELECT ; 
 unsigned int AC_WID_AUD_IN ; 
 int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_iprintf (struct snd_info_buffer*,char*,int,...) ; 

__attribute__((used)) static void print_audio_io(struct snd_info_buffer *buffer,
			   struct hda_codec *codec, hda_nid_t nid,
			   unsigned int wid_type)
{
	int conv = snd_hda_codec_read(codec, nid, 0, AC_VERB_GET_CONV, 0);
	snd_iprintf(buffer,
		    "  Converter: stream=%d, channel=%d\n",
		    (conv & AC_CONV_STREAM) >> AC_CONV_STREAM_SHIFT,
		    conv & AC_CONV_CHANNEL);

	if (wid_type == AC_WID_AUD_IN && (conv & AC_CONV_CHANNEL) == 0) {
		int sdi = snd_hda_codec_read(codec, nid, 0,
					     AC_VERB_GET_SDI_SELECT, 0);
		snd_iprintf(buffer, "  SDI-Select: %d\n",
			    sdi & AC_SDI_SELECT);
	}
}