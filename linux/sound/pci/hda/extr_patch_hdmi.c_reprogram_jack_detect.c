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
struct hda_jack_tbl {unsigned int tag; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_USRSP_EN ; 
 int /*<<< orphan*/  AC_VERB_SET_UNSOLICITED_ENABLE ; 
 int /*<<< orphan*/  snd_hda_codec_write_cache (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  snd_hda_jack_detect_enable (struct hda_codec*,int /*<<< orphan*/ ) ; 
 struct hda_jack_tbl* snd_hda_jack_tbl_get (struct hda_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reprogram_jack_detect(struct hda_codec *codec, hda_nid_t nid,
				  bool use_acomp)
{
	struct hda_jack_tbl *tbl;

	tbl = snd_hda_jack_tbl_get(codec, nid);
	if (tbl) {
		/* clear unsol even if component notifier is used, or re-enable
		 * if notifier is cleared
		 */
		unsigned int val = use_acomp ? 0 : (AC_USRSP_EN | tbl->tag);
		snd_hda_codec_write_cache(codec, nid, 0,
					  AC_VERB_SET_UNSOLICITED_ENABLE, val);
	} else {
		/* if no jack entry was defined beforehand, create a new one
		 * at need (i.e. only when notifier is cleared)
		 */
		if (!use_acomp)
			snd_hda_jack_detect_enable(codec, nid);
	}
}