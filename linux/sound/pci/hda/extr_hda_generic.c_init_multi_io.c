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
struct nid_path {int /*<<< orphan*/  active; } ;
struct hda_gen_spec {int multi_ios; TYPE_1__* multi_io; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;
struct TYPE_2__ {int /*<<< orphan*/  ctl_in; int /*<<< orphan*/  pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  aamix_default (struct hda_gen_spec*) ; 
 struct nid_path* get_multiio_path (struct hda_codec*,int) ; 
 int /*<<< orphan*/  snd_hda_activate_path (struct hda_codec*,struct nid_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_get_pin_target (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_multi_io(struct hda_codec *codec)
{
	struct hda_gen_spec *spec = codec->spec;
	int i;

	for (i = 0; i < spec->multi_ios; i++) {
		hda_nid_t pin = spec->multi_io[i].pin;
		struct nid_path *path;
		path = get_multiio_path(codec, i);
		if (!path)
			continue;
		if (!spec->multi_io[i].ctl_in)
			spec->multi_io[i].ctl_in =
				snd_hda_codec_get_pin_target(codec, pin);
		snd_hda_activate_path(codec, path, path->active,
				      aamix_default(spec));
	}
}