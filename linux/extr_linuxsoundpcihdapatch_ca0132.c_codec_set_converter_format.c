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
 int /*<<< orphan*/  VENDOR_CHIPIO_STREAM_FORMAT ; 
 int codec_send_command (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short,unsigned int*) ; 

__attribute__((used)) static int codec_set_converter_format(struct hda_codec *codec, hda_nid_t nid,
		unsigned short converter_format, unsigned int *res)
{
	return codec_send_command(codec, nid, VENDOR_CHIPIO_STREAM_FORMAT,
				converter_format & 0xffff, res);
}