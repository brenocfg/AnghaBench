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
struct hda_codec {int /*<<< orphan*/  core; int /*<<< orphan*/  dp_mst; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int AC_DEV_LIST_LEN_MASK ; 
 int /*<<< orphan*/  AC_PAR_DEVLIST_LEN ; 
 unsigned int AC_WCAP_DIGITAL ; 
 scalar_t__ AC_WID_PIN ; 
 unsigned int get_wcaps (struct hda_codec*,int /*<<< orphan*/ ) ; 
 scalar_t__ get_wcaps_type (unsigned int) ; 
 unsigned int snd_hdac_read_parm_uncached (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int snd_hda_get_num_devices(struct hda_codec *codec, hda_nid_t nid)
{
	unsigned int wcaps = get_wcaps(codec, nid);
	unsigned int parm;

	if (!codec->dp_mst || !(wcaps & AC_WCAP_DIGITAL) ||
	    get_wcaps_type(wcaps) != AC_WID_PIN)
		return 0;

	parm = snd_hdac_read_parm_uncached(&codec->core, nid, AC_PAR_DEVLIST_LEN);
	if (parm == -1)
		parm = 0;
	return parm & AC_DEV_LIST_LEN_MASK;
}