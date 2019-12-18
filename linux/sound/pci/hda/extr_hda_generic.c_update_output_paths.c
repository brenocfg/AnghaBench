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
struct nid_path {int /*<<< orphan*/  active; } ;
struct hda_gen_spec {int /*<<< orphan*/  aamix_mode; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_hda_activate_path (struct hda_codec*,struct nid_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nid_path* snd_hda_get_path_from_idx (struct hda_codec*,int const) ; 

__attribute__((used)) static void update_output_paths(struct hda_codec *codec, int num_outs,
				const int *paths)
{
	struct hda_gen_spec *spec = codec->spec;
	struct nid_path *path;
	int i;

	for (i = 0; i < num_outs; i++) {
		path = snd_hda_get_path_from_idx(codec, paths[i]);
		if (path)
			snd_hda_activate_path(codec, path, path->active,
					      spec->aamix_mode);
	}
}