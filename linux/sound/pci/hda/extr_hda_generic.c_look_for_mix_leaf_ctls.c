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
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 unsigned int HDA_COMPOSE_AMP_VAL (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_INPUT ; 
 int /*<<< orphan*/  HDA_OUTPUT ; 
 int /*<<< orphan*/  NID_PATH_MUTE_CTL ; 
 int /*<<< orphan*/  NID_PATH_VOL_CTL ; 
 int /*<<< orphan*/  is_ctl_associated (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nid_has_mute (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nid_has_volume (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_hda_get_conn_index (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int snd_hda_get_conn_list (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static bool look_for_mix_leaf_ctls(struct hda_codec *codec, hda_nid_t mix_nid,
				   hda_nid_t pin, unsigned int *mix_val,
				   unsigned int *mute_val)
{
	int idx, num_conns;
	const hda_nid_t *list;
	hda_nid_t nid;

	idx = snd_hda_get_conn_index(codec, mix_nid, pin, true);
	if (idx < 0)
		return false;

	*mix_val = *mute_val = 0;
	if (nid_has_volume(codec, mix_nid, HDA_INPUT))
		*mix_val = HDA_COMPOSE_AMP_VAL(mix_nid, 3, idx, HDA_INPUT);
	if (nid_has_mute(codec, mix_nid, HDA_INPUT))
		*mute_val = HDA_COMPOSE_AMP_VAL(mix_nid, 3, idx, HDA_INPUT);
	if (*mix_val && *mute_val)
		return true;

	/* check leaf node */
	num_conns = snd_hda_get_conn_list(codec, mix_nid, &list);
	if (num_conns < idx)
		return false;
	nid = list[idx];
	if (!*mix_val && nid_has_volume(codec, nid, HDA_OUTPUT) &&
	    !is_ctl_associated(codec, nid, HDA_OUTPUT, 0, NID_PATH_VOL_CTL))
		*mix_val = HDA_COMPOSE_AMP_VAL(nid, 3, 0, HDA_OUTPUT);
	if (!*mute_val && nid_has_mute(codec, nid, HDA_OUTPUT) &&
	    !is_ctl_associated(codec, nid, HDA_OUTPUT, 0, NID_PATH_MUTE_CTL))
		*mute_val = HDA_COMPOSE_AMP_VAL(nid, 3, 0, HDA_OUTPUT);

	return *mix_val || *mute_val;
}