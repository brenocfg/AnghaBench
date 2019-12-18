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
struct hda_gen_spec {int num_all_dacs; scalar_t__* all_dacs; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 scalar_t__ is_dac_already_used (struct hda_codec*,scalar_t__) ; 
 scalar_t__ is_reachable_path (struct hda_codec*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static hda_nid_t get_dac_if_single(struct hda_codec *codec, hda_nid_t pin)
{
	struct hda_gen_spec *spec = codec->spec;
	int i;
	hda_nid_t nid_found = 0;

	for (i = 0; i < spec->num_all_dacs; i++) {
		hda_nid_t nid = spec->all_dacs[i];
		if (!nid || is_dac_already_used(codec, nid))
			continue;
		if (is_reachable_path(codec, nid, pin)) {
			if (nid_found)
				return 0;
			nid_found = nid;
		}
	}
	return nid_found;
}