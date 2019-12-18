#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hda_codec {struct ad198x_spec* spec; } ;
struct TYPE_2__ {int mixer_nid; int beep_nid; } ;
struct ad198x_spec {TYPE_1__ gen; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 int ad1983_add_spdif_mux_ctl (struct hda_codec*) ; 
 int ad198x_parse_auto_config (struct hda_codec*,int) ; 
 int alloc_ad_spec (struct hda_codec*) ; 
 int /*<<< orphan*/  set_beep_amp (struct ad198x_spec*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_gen_free (struct hda_codec*) ; 
 int /*<<< orphan*/  snd_hda_override_conn_list (struct hda_codec*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int patch_ad1983(struct hda_codec *codec)
{
	struct ad198x_spec *spec;
	static hda_nid_t conn_0c[] = { 0x08 };
	static hda_nid_t conn_0d[] = { 0x09 };
	int err;

	err = alloc_ad_spec(codec);
	if (err < 0)
		return err;
	spec = codec->spec;

	spec->gen.mixer_nid = 0x0e;
	spec->gen.beep_nid = 0x10;
	set_beep_amp(spec, 0x10, 0, HDA_OUTPUT);

	/* limit the loopback routes not to confuse the parser */
	snd_hda_override_conn_list(codec, 0x0c, ARRAY_SIZE(conn_0c), conn_0c);
	snd_hda_override_conn_list(codec, 0x0d, ARRAY_SIZE(conn_0d), conn_0d);

	err = ad198x_parse_auto_config(codec, false);
	if (err < 0)
		goto error;
	err = ad1983_add_spdif_mux_ctl(codec);
	if (err < 0)
		goto error;
	return 0;

 error:
	snd_hda_gen_free(codec);
	return err;
}