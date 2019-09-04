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
struct nid_path {int* idx; int depth; unsigned int* ctls; int active; int stream_enabled; int pin_fixed; } ;
struct hda_gen_spec {scalar_t__ mixer_nid; scalar_t__ mixer_merge_nid; void* loopback_merge_path; void** loopback_paths; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HDA_CTL_WIDGET_MUTE ; 
 int /*<<< orphan*/  HDA_CTL_WIDGET_VOL ; 
 size_t NID_PATH_MUTE_CTL ; 
 size_t NID_PATH_VOL_CTL ; 
 int __add_pb_sw_ctrl (struct hda_gen_spec*,int /*<<< orphan*/ ,char const*,int,unsigned int) ; 
 int __add_pb_vol_ctrl (struct hda_gen_spec*,int /*<<< orphan*/ ,char const*,int,unsigned int) ; 
 int add_loopback_list (struct hda_gen_spec*,scalar_t__,int) ; 
 int /*<<< orphan*/  look_for_mix_leaf_ctls (struct hda_codec*,scalar_t__,scalar_t__,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  print_nid_path (struct hda_codec*,char*,struct nid_path*) ; 
 struct nid_path* snd_hda_add_new_path (struct hda_codec*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 void* snd_hda_get_path_idx (struct hda_codec*,struct nid_path*) ; 

__attribute__((used)) static int new_analog_input(struct hda_codec *codec, int input_idx,
			    hda_nid_t pin, const char *ctlname, int ctlidx,
			    hda_nid_t mix_nid)
{
	struct hda_gen_spec *spec = codec->spec;
	struct nid_path *path;
	unsigned int mix_val, mute_val;
	int err, idx;

	if (!look_for_mix_leaf_ctls(codec, mix_nid, pin, &mix_val, &mute_val))
		return 0;

	path = snd_hda_add_new_path(codec, pin, mix_nid, 0);
	if (!path)
		return -EINVAL;
	print_nid_path(codec, "loopback", path);
	spec->loopback_paths[input_idx] = snd_hda_get_path_idx(codec, path);

	idx = path->idx[path->depth - 1];
	if (mix_val) {
		err = __add_pb_vol_ctrl(spec, HDA_CTL_WIDGET_VOL, ctlname, ctlidx, mix_val);
		if (err < 0)
			return err;
		path->ctls[NID_PATH_VOL_CTL] = mix_val;
	}

	if (mute_val) {
		err = __add_pb_sw_ctrl(spec, HDA_CTL_WIDGET_MUTE, ctlname, ctlidx, mute_val);
		if (err < 0)
			return err;
		path->ctls[NID_PATH_MUTE_CTL] = mute_val;
	}

	path->active = true;
	path->stream_enabled = true; /* no DAC/ADC involved */
	err = add_loopback_list(spec, mix_nid, idx);
	if (err < 0)
		return err;

	if (spec->mixer_nid != spec->mixer_merge_nid &&
	    !spec->loopback_merge_path) {
		path = snd_hda_add_new_path(codec, spec->mixer_nid,
					    spec->mixer_merge_nid, 0);
		if (path) {
			print_nid_path(codec, "loopback-merge", path);
			path->active = true;
			path->pin_fixed = true; /* static route */
			path->stream_enabled = true; /* no DAC/ADC involved */
			spec->loopback_merge_path =
				snd_hda_get_path_idx(codec, path);
		}
	}

	return 0;
}