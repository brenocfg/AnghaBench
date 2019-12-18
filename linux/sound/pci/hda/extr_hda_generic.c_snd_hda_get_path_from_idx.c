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
struct TYPE_2__ {int used; } ;
struct hda_gen_spec {TYPE_1__ paths; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;

/* Variables and functions */
 struct nid_path* snd_array_elem (TYPE_1__*,int) ; 

struct nid_path *snd_hda_get_path_from_idx(struct hda_codec *codec, int idx)
{
	struct hda_gen_spec *spec = codec->spec;

	if (idx <= 0 || idx > spec->paths.used)
		return NULL;
	return snd_array_elem(&spec->paths, idx - 1);
}