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
struct hda_codec {struct ca0132_spec* spec; } ;
struct ca0132_spec {int /*<<< orphan*/ * adcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_VERB_GET_CONV ; 
 int /*<<< orphan*/  AC_VERB_SET_CHANNEL_STREAMID ; 
 unsigned int snd_hda_codec_read (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stop_mic1(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	unsigned int oldval = snd_hda_codec_read(codec, spec->adcs[0], 0,
						 AC_VERB_GET_CONV, 0);
	if (oldval != 0)
		snd_hda_codec_write(codec, spec->adcs[0], 0,
				    AC_VERB_SET_CHANNEL_STREAMID,
				    0);
	return oldval;
}