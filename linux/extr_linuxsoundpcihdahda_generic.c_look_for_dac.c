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
struct hda_gen_spec {int num_all_dacs; int /*<<< orphan*/ * all_dacs; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int AC_WCAP_DIGITAL ; 
 int get_wcaps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_dac_already_used (struct hda_codec*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_reachable_path (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static hda_nid_t look_for_dac(struct hda_codec *codec, hda_nid_t pin,
			      bool is_digital)
{
	struct hda_gen_spec *spec = codec->spec;
	bool cap_digital;
	int i;

	for (i = 0; i < spec->num_all_dacs; i++) {
		hda_nid_t nid = spec->all_dacs[i];
		if (!nid || is_dac_already_used(codec, nid))
			continue;
		cap_digital = !!(get_wcaps(codec, nid) & AC_WCAP_DIGITAL);
		if (is_digital != cap_digital)
			continue;
		if (is_reachable_path(codec, nid, pin))
			return nid;
	}
	return 0;
}