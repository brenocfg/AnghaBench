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
struct nid_path {int dummy; } ;
struct TYPE_2__ {int used; struct nid_path* list; } ;
struct hda_gen_spec {TYPE_1__ paths; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int ssize_t ;

/* Variables and functions */

int snd_hda_get_path_idx(struct hda_codec *codec, struct nid_path *path)
{
	struct hda_gen_spec *spec = codec->spec;
	struct nid_path *array = spec->paths.list;
	ssize_t idx;

	if (!spec->paths.used)
		return 0;
	idx = path - array;
	if (idx < 0 || idx >= spec->paths.used)
		return 0;
	return idx + 1;
}