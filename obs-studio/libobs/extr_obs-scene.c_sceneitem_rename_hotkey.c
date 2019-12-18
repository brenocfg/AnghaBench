#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dstr {int /*<<< orphan*/  array; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int /*<<< orphan*/  toggle_visibility; } ;
typedef  TYPE_2__ obs_sceneitem_t ;
struct TYPE_5__ {char* sceneitem_show; char* sceneitem_hide; } ;
struct TYPE_7__ {TYPE_1__ hotkeys; } ;

/* Variables and functions */
 int /*<<< orphan*/  dstr_copy (struct dstr*,char*) ; 
 int /*<<< orphan*/  dstr_free (struct dstr*) ; 
 int /*<<< orphan*/  dstr_replace (struct dstr*,char*,char const*) ; 
 TYPE_4__* obs ; 
 int /*<<< orphan*/  obs_hotkey_pair_set_descriptions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_hotkey_pair_set_names (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sceneitem_rename_hotkey(const obs_sceneitem_t *scene_item,
				    const char *new_name)
{
	struct dstr show = {0};
	struct dstr hide = {0};
	struct dstr show_desc = {0};
	struct dstr hide_desc = {0};

	dstr_copy(&show, "libobs.show_scene_item.%1");
	dstr_replace(&show, "%1", new_name);
	dstr_copy(&hide, "libobs.hide_scene_item.%1");
	dstr_replace(&hide, "%1", new_name);

	obs_hotkey_pair_set_names(scene_item->toggle_visibility, show.array,
				  hide.array);

	dstr_copy(&show_desc, obs->hotkeys.sceneitem_show);
	dstr_replace(&show_desc, "%1", new_name);
	dstr_copy(&hide_desc, obs->hotkeys.sceneitem_hide);
	dstr_replace(&hide_desc, "%1", new_name);

	obs_hotkey_pair_set_descriptions(scene_item->toggle_visibility,
					 show_desc.array, hide_desc.array);

	dstr_free(&show);
	dstr_free(&hide);
	dstr_free(&show_desc);
	dstr_free(&hide_desc);
}