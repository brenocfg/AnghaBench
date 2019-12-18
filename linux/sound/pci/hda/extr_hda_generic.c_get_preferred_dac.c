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
struct hda_gen_spec {scalar_t__* preferred_dacs; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  scalar_t__ const hda_nid_t ;

/* Variables and functions */

__attribute__((used)) static hda_nid_t get_preferred_dac(struct hda_codec *codec, hda_nid_t pin)
{
	struct hda_gen_spec *spec = codec->spec;
	const hda_nid_t *list = spec->preferred_dacs;

	if (!list)
		return 0;
	for (; *list; list += 2)
		if (*list == pin)
			return list[1];
	return 0;
}