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
struct nid_path {int active; } ;
struct hda_gen_spec {TYPE_1__* multi_io; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
struct TYPE_2__ {int /*<<< orphan*/  ctl_in; int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PIN_OUT ; 
 int /*<<< orphan*/  aamix_default (struct hda_gen_spec*) ; 
 struct nid_path* get_multiio_path (struct hda_codec*,int) ; 
 int /*<<< orphan*/  path_power_down_sync (struct hda_codec*,struct nid_path*) ; 
 int /*<<< orphan*/  set_pin_eapd (struct hda_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_pin_target (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hda_activate_path (struct hda_codec*,struct nid_path*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_automute_all (struct hda_codec*) ; 

__attribute__((used)) static int set_multi_io(struct hda_codec *codec, int idx, bool output)
{
	struct hda_gen_spec *spec = codec->spec;
	hda_nid_t nid = spec->multi_io[idx].pin;
	struct nid_path *path;

	path = get_multiio_path(codec, idx);
	if (!path)
		return -EINVAL;

	if (path->active == output)
		return 0;

	if (output) {
		set_pin_target(codec, nid, PIN_OUT, true);
		snd_hda_activate_path(codec, path, true, aamix_default(spec));
		set_pin_eapd(codec, nid, true);
	} else {
		set_pin_eapd(codec, nid, false);
		snd_hda_activate_path(codec, path, false, aamix_default(spec));
		set_pin_target(codec, nid, spec->multi_io[idx].ctl_in, true);
		path_power_down_sync(codec, path);
	}

	/* update jack retasking in case it modifies any of them */
	update_automute_all(codec);

	return 0;
}