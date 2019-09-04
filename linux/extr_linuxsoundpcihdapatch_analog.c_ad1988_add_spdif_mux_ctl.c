#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nid_path {int depth; int active; int /*<<< orphan*/  multi; int /*<<< orphan*/  idx; int /*<<< orphan*/  path; } ;
struct TYPE_5__ {int /*<<< orphan*/  init; } ;
struct hda_codec {TYPE_2__ patch_ops; struct ad198x_spec* spec; } ;
struct TYPE_4__ {int /*<<< orphan*/  dig_outs; } ;
struct TYPE_6__ {int /*<<< orphan*/  paths; TYPE_1__ autocfg; } ;
struct ad198x_spec {TYPE_3__ gen; int /*<<< orphan*/ * smux_paths; } ;

/* Variables and functions */
 scalar_t__ AC_WID_AUD_MIX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ad1988_auto_init ; 
 int /*<<< orphan*/  ad1988_auto_smux_mixer ; 
 int /*<<< orphan*/  get_wcaps (struct hda_codec*,int) ; 
 scalar_t__ get_wcaps_type (int /*<<< orphan*/ ) ; 
 struct nid_path* snd_array_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hda_gen_add_kctl (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int snd_hda_get_num_conns (struct hda_codec*,int) ; 
 int /*<<< orphan*/  snd_hda_get_path_idx (struct hda_codec*,struct nid_path*) ; 

__attribute__((used)) static int ad1988_add_spdif_mux_ctl(struct hda_codec *codec)
{
	struct ad198x_spec *spec = codec->spec;
	int i, num_conns;
	/* we create four static faked paths, since AD codecs have odd
	 * widget connections regarding the SPDIF out source
	 */
	static struct nid_path fake_paths[4] = {
		{
			.depth = 3,
			.path = { 0x02, 0x1d, 0x1b },
			.idx = { 0, 0, 0 },
			.multi = { 0, 0, 0 },
		},
		{
			.depth = 4,
			.path = { 0x08, 0x0b, 0x1d, 0x1b },
			.idx = { 0, 0, 1, 0 },
			.multi = { 0, 1, 0, 0 },
		},
		{
			.depth = 4,
			.path = { 0x09, 0x0b, 0x1d, 0x1b },
			.idx = { 0, 1, 1, 0 },
			.multi = { 0, 1, 0, 0 },
		},
		{
			.depth = 4,
			.path = { 0x0f, 0x0b, 0x1d, 0x1b },
			.idx = { 0, 2, 1, 0 },
			.multi = { 0, 1, 0, 0 },
		},
	};

	/* SPDIF source mux appears to be present only on AD1988A */
	if (!spec->gen.autocfg.dig_outs ||
	    get_wcaps_type(get_wcaps(codec, 0x1d)) != AC_WID_AUD_MIX)
		return 0;

	num_conns = snd_hda_get_num_conns(codec, 0x0b) + 1;
	if (num_conns != 3 && num_conns != 4)
		return 0;

	for (i = 0; i < num_conns; i++) {
		struct nid_path *path = snd_array_new(&spec->gen.paths);
		if (!path)
			return -ENOMEM;
		*path = fake_paths[i];
		if (!i)
			path->active = 1;
		spec->smux_paths[i] = snd_hda_get_path_idx(codec, path);
	}

	if (!snd_hda_gen_add_kctl(&spec->gen, NULL, &ad1988_auto_smux_mixer))
		return -ENOMEM;

	codec->patch_ops.init = ad1988_auto_init;

	return 0;
}