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
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_SET_CHANNEL_STREAMID ; 
 int codec_send_command (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,unsigned int*) ; 

__attribute__((used)) static int codec_set_converter_stream_channel(struct hda_codec *codec,
				hda_nid_t nid, unsigned char stream,
				unsigned char channel, unsigned int *res)
{
	unsigned char converter_stream_channel = 0;

	converter_stream_channel = (stream << 4) | (channel & 0x0f);
	return codec_send_command(codec, nid, AC_VERB_SET_CHANNEL_STREAMID,
				converter_stream_channel, res);
}