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
struct nid_path {int dummy; } ;
struct hda_gen_spec {scalar_t__ multi_ios; int /*<<< orphan*/ * out_paths; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
struct auto_pin_cfg {int line_outs; } ;

/* Variables and functions */
 int /*<<< orphan*/  NID_PATH_MUTE_CTL ; 
 int /*<<< orphan*/  NID_PATH_VOL_CTL ; 
 int add_stereo_sw (struct hda_codec*,char const*,int,struct nid_path*) ; 
 int add_stereo_vol (struct hda_codec*,char const*,int,struct nid_path*) ; 
 int add_sw_ctl (struct hda_codec*,char*,int /*<<< orphan*/ ,int,struct nid_path*) ; 
 int add_vol_ctl (struct hda_codec*,char*,int /*<<< orphan*/ ,int,struct nid_path*) ; 
 char* get_line_out_pfx (struct hda_codec*,int,int*,int /*<<< orphan*/ ) ; 
 struct nid_path* snd_hda_get_path_from_idx (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int create_multi_out_ctls(struct hda_codec *codec,
				 const struct auto_pin_cfg *cfg)
{
	struct hda_gen_spec *spec = codec->spec;
	int i, err, noutputs;

	noutputs = cfg->line_outs;
	if (spec->multi_ios > 0 && cfg->line_outs < 3)
		noutputs += spec->multi_ios;

	for (i = 0; i < noutputs; i++) {
		const char *name;
		int index;
		struct nid_path *path;

		path = snd_hda_get_path_from_idx(codec, spec->out_paths[i]);
		if (!path)
			continue;

		name = get_line_out_pfx(codec, i, &index, NID_PATH_VOL_CTL);
		if (!name || !strcmp(name, "CLFE")) {
			/* Center/LFE */
			err = add_vol_ctl(codec, "Center", 0, 1, path);
			if (err < 0)
				return err;
			err = add_vol_ctl(codec, "LFE", 0, 2, path);
			if (err < 0)
				return err;
		} else {
			err = add_stereo_vol(codec, name, index, path);
			if (err < 0)
				return err;
		}

		name = get_line_out_pfx(codec, i, &index, NID_PATH_MUTE_CTL);
		if (!name || !strcmp(name, "CLFE")) {
			err = add_sw_ctl(codec, "Center", 0, 1, path);
			if (err < 0)
				return err;
			err = add_sw_ctl(codec, "LFE", 0, 2, path);
			if (err < 0)
				return err;
		} else {
			err = add_stereo_sw(codec, name, index, path);
			if (err < 0)
				return err;
		}
	}
	return 0;
}