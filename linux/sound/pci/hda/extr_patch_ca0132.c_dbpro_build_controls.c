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
struct ca0132_spec {scalar_t__ dig_in; scalar_t__ dig_out; } ;

/* Variables and functions */
 int snd_hda_create_spdif_in_ctls (struct hda_codec*,scalar_t__) ; 
 int snd_hda_create_spdif_out_ctls (struct hda_codec*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int dbpro_build_controls(struct hda_codec *codec)
{
	struct ca0132_spec *spec = codec->spec;
	int err = 0;

	if (spec->dig_out) {
		err = snd_hda_create_spdif_out_ctls(codec, spec->dig_out,
				spec->dig_out);
		if (err < 0)
			return err;
	}

	if (spec->dig_in) {
		err = snd_hda_create_spdif_in_ctls(codec, spec->dig_in);
		if (err < 0)
			return err;
	}

	return 0;
}