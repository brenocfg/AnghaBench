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
struct nid_path {size_t depth; int /*<<< orphan*/ * path; } ;
struct hda_codec {int dummy; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 scalar_t__ __parse_nid_path (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nid_path*,int) ; 

__attribute__((used)) static bool snd_hda_parse_nid_path(struct hda_codec *codec, hda_nid_t from_nid,
			    hda_nid_t to_nid, int anchor_nid,
			    struct nid_path *path)
{
	if (__parse_nid_path(codec, from_nid, to_nid, anchor_nid, path, 1)) {
		path->path[path->depth] = to_nid;
		path->depth++;
		return true;
	}
	return false;
}