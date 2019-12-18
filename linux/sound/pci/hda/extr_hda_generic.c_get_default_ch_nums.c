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
struct nid_path {int /*<<< orphan*/ * ctls; } ;
struct hda_codec {int dummy; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 int AC_WCAP_STEREO ; 
 scalar_t__ get_amp_nid_ (int /*<<< orphan*/ ) ; 
 int get_wcaps (struct hda_codec*,scalar_t__) ; 

__attribute__((used)) static int get_default_ch_nums(struct hda_codec *codec, struct nid_path *path,
			       int type)
{
	int chs = 1; /* mono (left only) */
	if (path) {
		hda_nid_t nid = get_amp_nid_(path->ctls[type]);
		if (nid && (get_wcaps(codec, nid) & AC_WCAP_STEREO))
			chs = 3; /* stereo */
	}
	return chs;
}