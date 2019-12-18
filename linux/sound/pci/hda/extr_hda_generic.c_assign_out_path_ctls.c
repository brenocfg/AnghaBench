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
struct nid_path {unsigned int* ctls; } ;
struct hda_gen_spec {scalar_t__ dac_min_mute; } ;
struct hda_codec {struct hda_gen_spec* spec; } ;
typedef  scalar_t__ hda_nid_t ;

/* Variables and functions */
 unsigned int AC_WID_AUD_OUT ; 
 unsigned int AC_WID_PIN ; 
 int BAD_SHARED_VOL ; 
 unsigned int HDA_AMP_VAL_MIN_MUTE ; 
 unsigned int HDA_COMPOSE_AMP_VAL (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 size_t NID_PATH_MUTE_CTL ; 
 size_t NID_PATH_VOL_CTL ; 
 int /*<<< orphan*/  get_wcaps (struct hda_codec*,scalar_t__) ; 
 unsigned int get_wcaps_type (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ctl_used (struct hda_codec*,unsigned int,size_t) ; 
 scalar_t__ look_for_out_mute_nid (struct hda_codec*,struct nid_path*) ; 
 scalar_t__ look_for_out_vol_nid (struct hda_codec*,struct nid_path*) ; 
 scalar_t__ nid_has_mute (struct hda_codec*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int assign_out_path_ctls(struct hda_codec *codec, struct nid_path *path)
{
	struct hda_gen_spec *spec = codec->spec;
	hda_nid_t nid;
	unsigned int val;
	int badness = 0;

	if (!path)
		return BAD_SHARED_VOL * 2;

	if (path->ctls[NID_PATH_VOL_CTL] ||
	    path->ctls[NID_PATH_MUTE_CTL])
		return 0; /* already evaluated */

	nid = look_for_out_vol_nid(codec, path);
	if (nid) {
		val = HDA_COMPOSE_AMP_VAL(nid, 3, 0, HDA_OUTPUT);
		if (spec->dac_min_mute)
			val |= HDA_AMP_VAL_MIN_MUTE;
		if (is_ctl_used(codec, val, NID_PATH_VOL_CTL))
			badness += BAD_SHARED_VOL;
		else
			path->ctls[NID_PATH_VOL_CTL] = val;
	} else
		badness += BAD_SHARED_VOL;
	nid = look_for_out_mute_nid(codec, path);
	if (nid) {
		unsigned int wid_type = get_wcaps_type(get_wcaps(codec, nid));
		if (wid_type == AC_WID_PIN || wid_type == AC_WID_AUD_OUT ||
		    nid_has_mute(codec, nid, HDA_OUTPUT))
			val = HDA_COMPOSE_AMP_VAL(nid, 3, 0, HDA_OUTPUT);
		else
			val = HDA_COMPOSE_AMP_VAL(nid, 3, 0, HDA_INPUT);
		if (is_ctl_used(codec, val, NID_PATH_MUTE_CTL))
			badness += BAD_SHARED_VOL;
		else
			path->ctls[NID_PATH_MUTE_CTL] = val;
	} else
		badness += BAD_SHARED_VOL;
	return badness;
}