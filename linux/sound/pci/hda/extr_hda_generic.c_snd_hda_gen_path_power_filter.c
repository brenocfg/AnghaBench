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
struct hda_gen_spec {int /*<<< orphan*/  power_down_unused; } ;
struct TYPE_2__ {scalar_t__ afg; } ;
struct hda_codec {TYPE_1__ core; int /*<<< orphan*/  power_save_node; struct hda_gen_spec* spec; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 unsigned int AC_PWRST_D0 ; 
 unsigned int AC_PWRST_D3 ; 
 scalar_t__ AC_WID_POWER ; 
 int /*<<< orphan*/  get_wcaps (struct hda_codec*,scalar_t__) ; 
 scalar_t__ get_wcaps_type (int /*<<< orphan*/ ) ; 
 scalar_t__ is_active_nid_for_any (struct hda_codec*,scalar_t__) ; 

unsigned int snd_hda_gen_path_power_filter(struct hda_codec *codec,
						  hda_nid_t nid,
						  unsigned int power_state)
{
	struct hda_gen_spec *spec = codec->spec;

	if (!spec->power_down_unused && !codec->power_save_node)
		return power_state;
	if (power_state != AC_PWRST_D0 || nid == codec->core.afg)
		return power_state;
	if (get_wcaps_type(get_wcaps(codec, nid)) >= AC_WID_POWER)
		return power_state;
	if (is_active_nid_for_any(codec, nid))
		return power_state;
	return AC_PWRST_D3;
}