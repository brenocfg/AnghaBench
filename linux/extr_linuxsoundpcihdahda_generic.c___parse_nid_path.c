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
struct nid_path {int* path; size_t depth; int* idx; int* multi; } ;
struct hda_codec {int dummy; } ;
typedef  int hda_nid_t ;

/* Variables and functions */
 unsigned int AC_WID_AUD_IN ; 
 unsigned int AC_WID_AUD_MIX ; 
 unsigned int AC_WID_AUD_OUT ; 
 unsigned int AC_WID_PIN ; 
 int MAX_NID_PATH_DEPTH ; 
 int /*<<< orphan*/  get_wcaps (struct hda_codec*,int const) ; 
 unsigned int get_wcaps_type (int /*<<< orphan*/ ) ; 
 scalar_t__ is_dac_already_used (struct hda_codec*,int const) ; 
 int snd_hda_get_conn_list (struct hda_codec*,int,int const**) ; 

__attribute__((used)) static bool __parse_nid_path(struct hda_codec *codec,
			     hda_nid_t from_nid, hda_nid_t to_nid,
			     int anchor_nid, struct nid_path *path,
			     int depth)
{
	const hda_nid_t *conn;
	int i, nums;

	if (to_nid == anchor_nid)
		anchor_nid = 0; /* anchor passed */
	else if (to_nid == (hda_nid_t)(-anchor_nid))
		return false; /* hit the exclusive nid */

	nums = snd_hda_get_conn_list(codec, to_nid, &conn);
	for (i = 0; i < nums; i++) {
		if (conn[i] != from_nid) {
			/* special case: when from_nid is 0,
			 * try to find an empty DAC
			 */
			if (from_nid ||
			    get_wcaps_type(get_wcaps(codec, conn[i])) != AC_WID_AUD_OUT ||
			    is_dac_already_used(codec, conn[i]))
				continue;
		}
		/* anchor is not requested or already passed? */
		if (anchor_nid <= 0)
			goto found;
	}
	if (depth >= MAX_NID_PATH_DEPTH)
		return false;
	for (i = 0; i < nums; i++) {
		unsigned int type;
		type = get_wcaps_type(get_wcaps(codec, conn[i]));
		if (type == AC_WID_AUD_OUT || type == AC_WID_AUD_IN ||
		    type == AC_WID_PIN)
			continue;
		if (__parse_nid_path(codec, from_nid, conn[i],
				     anchor_nid, path, depth + 1))
			goto found;
	}
	return false;

 found:
	path->path[path->depth] = conn[i];
	path->idx[path->depth + 1] = i;
	if (nums > 1 && get_wcaps_type(get_wcaps(codec, to_nid)) != AC_WID_AUD_MIX)
		path->multi[path->depth + 1] = 1;
	path->depth++;
	return true;
}