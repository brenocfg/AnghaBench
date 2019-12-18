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
struct nid_path {int depth; scalar_t__* path; } ;
struct TYPE_2__ {scalar_t__ afg; } ;
struct hda_codec {TYPE_1__ core; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int AC_PWRST_D0 ; 
 int AC_PWRST_D3 ; 
 int /*<<< orphan*/  AC_VERB_GET_POWER_STATE ; 
 int /*<<< orphan*/  AC_VERB_SET_POWER_STATE ; 
 int AC_WCAP_POWER ; 
 int get_wcaps (struct hda_codec*,scalar_t__) ; 
 scalar_t__ is_active_nid_for_any (struct hda_codec*,scalar_t__) ; 
 int snd_hda_codec_read (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_codec_write (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_hdac_regmap_sync_node (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static hda_nid_t path_power_update(struct hda_codec *codec,
				   struct nid_path *path,
				   bool allow_powerdown)
{
	hda_nid_t nid, changed = 0;
	int i, state, power;

	for (i = 0; i < path->depth; i++) {
		nid = path->path[i];
		if (!(get_wcaps(codec, nid) & AC_WCAP_POWER))
			continue;
		if (nid == codec->core.afg)
			continue;
		if (!allow_powerdown || is_active_nid_for_any(codec, nid))
			state = AC_PWRST_D0;
		else
			state = AC_PWRST_D3;
		power = snd_hda_codec_read(codec, nid, 0,
					   AC_VERB_GET_POWER_STATE, 0);
		if (power != (state | (state << 4))) {
			snd_hda_codec_write(codec, nid, 0,
					    AC_VERB_SET_POWER_STATE, state);
			changed = nid;
			/* all known codecs seem to be capable to handl
			 * widgets state even in D3, so far.
			 * if any new codecs need to restore the widget
			 * states after D0 transition, call the function
			 * below.
			 */
#if 0 /* disabled */
			if (state == AC_PWRST_D0)
				snd_hdac_regmap_sync_node(&codec->core, nid);
#endif
		}
	}
	return changed;
}