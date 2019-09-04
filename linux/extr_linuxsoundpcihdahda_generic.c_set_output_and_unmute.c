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
struct nid_path {int depth; int /*<<< orphan*/  active; int /*<<< orphan*/ * path; } ;
struct hda_codec {int /*<<< orphan*/  spec; } ;
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int /*<<< orphan*/  aamix_default (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restore_pin_ctl (struct hda_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pin_eapd (struct hda_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hda_activate_path (struct hda_codec*,struct nid_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nid_path* snd_hda_get_path_from_idx (struct hda_codec*,int) ; 

__attribute__((used)) static void set_output_and_unmute(struct hda_codec *codec, int path_idx)
{
	struct nid_path *path;
	hda_nid_t pin;

	path = snd_hda_get_path_from_idx(codec, path_idx);
	if (!path || !path->depth)
		return;
	pin = path->path[path->depth - 1];
	restore_pin_ctl(codec, pin);
	snd_hda_activate_path(codec, path, path->active,
			      aamix_default(codec->spec));
	set_pin_eapd(codec, pin, path->active);
}