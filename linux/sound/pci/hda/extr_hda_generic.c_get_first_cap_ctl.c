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
struct hda_codec {int dummy; } ;

/* Variables and functions */
 struct nid_path* get_input_path (struct hda_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int get_first_cap_ctl(struct hda_codec *codec, int idx, int type)
{
	struct nid_path *path;
	unsigned int ctl;
	int i;

	path = get_input_path(codec, 0, idx);
	if (!path)
		return 0;
	ctl = path->ctls[type];
	if (!ctl)
		return 0;
	for (i = 0; i < idx - 1; i++) {
		path = get_input_path(codec, 0, i);
		if (path && path->ctls[type] == ctl)
			return 0;
	}
	return ctl;
}