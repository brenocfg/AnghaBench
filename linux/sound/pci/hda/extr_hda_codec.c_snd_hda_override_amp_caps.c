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
struct hda_codec {int /*<<< orphan*/  core; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_PAR_AMP_IN_CAP ; 
 unsigned int AC_PAR_AMP_OUT_CAP ; 
 int AC_WCAP_AMP_OVRD ; 
 int HDA_OUTPUT ; 
 int get_wcaps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_override_wcaps (struct hda_codec*,int /*<<< orphan*/ ,int) ; 
 int snd_hdac_override_parm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

int snd_hda_override_amp_caps(struct hda_codec *codec, hda_nid_t nid, int dir,
			      unsigned int caps)
{
	unsigned int parm;

	snd_hda_override_wcaps(codec, nid,
			       get_wcaps(codec, nid) | AC_WCAP_AMP_OVRD);
	parm = dir == HDA_OUTPUT ? AC_PAR_AMP_OUT_CAP : AC_PAR_AMP_IN_CAP;
	return snd_hdac_override_parm(&codec->core, nid, parm, caps);
}