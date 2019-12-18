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
struct nid_path {scalar_t__* ctls; } ;
struct hda_codec {int dummy; } ;

/* Variables and functions */
 struct nid_path* snd_hda_get_path_from_idx (struct hda_codec*,int) ; 

__attribute__((used)) static bool path_has_mixer(struct hda_codec *codec, int path_idx, int ctl_type)
{
	struct nid_path *path = snd_hda_get_path_from_idx(codec, path_idx);
	return path && path->ctls[ctl_type];
}