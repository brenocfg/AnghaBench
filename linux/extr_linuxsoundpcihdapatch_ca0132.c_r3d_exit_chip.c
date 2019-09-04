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
 int /*<<< orphan*/  ca0132_clear_unsolicited (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void r3d_exit_chip(struct hda_codec *codec)
{
	ca0132_clear_unsolicited(codec);
	snd_hda_codec_write(codec, 0x01, 0, 0x793, 0x00);
	snd_hda_codec_write(codec, 0x01, 0, 0x794, 0x5b);
}