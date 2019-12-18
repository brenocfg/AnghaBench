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
struct snd_array {int dummy; } ;
struct hda_pincfg {unsigned int cfg; int /*<<< orphan*/  nid; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct hda_pincfg* look_up_pincfg (struct hda_codec*,struct snd_array*,int /*<<< orphan*/ ) ; 
 struct hda_pincfg* snd_array_new (struct snd_array*) ; 

int snd_hda_add_pincfg(struct hda_codec *codec, struct snd_array *list,
		       hda_nid_t nid, unsigned int cfg)
{
	struct hda_pincfg *pin;

	/* the check below may be invalid when pins are added by a fixup
	 * dynamically (e.g. via snd_hda_codec_update_widgets()), so disabled
	 * for now
	 */
	/*
	if (get_wcaps_type(get_wcaps(codec, nid)) != AC_WID_PIN)
		return -EINVAL;
	*/

	pin = look_up_pincfg(codec, list, nid);
	if (!pin) {
		pin = snd_array_new(list);
		if (!pin)
			return -ENOMEM;
		pin->nid = nid;
	}
	pin->cfg = cfg;
	return 0;
}