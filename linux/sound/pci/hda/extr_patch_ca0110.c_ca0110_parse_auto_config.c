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
struct hda_gen_spec {int /*<<< orphan*/  autocfg; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int snd_hda_gen_parse_auto_config (struct hda_codec*,int /*<<< orphan*/ *) ; 
 int snd_hda_parse_pin_defcfg (struct hda_codec*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ca0110_parse_auto_config(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	int err;

	err = snd_hda_parse_pin_defcfg(codec, &spec->autocfg, NULL, 0);
	if (err < 0)
		return err;
	err = snd_hda_gen_parse_auto_config(codec, &spec->autocfg);
	if (err < 0)
		return err;

	return 0;
}