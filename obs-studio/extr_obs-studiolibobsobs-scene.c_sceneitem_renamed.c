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
typedef  int /*<<< orphan*/  obs_sceneitem_t ;
typedef  int /*<<< orphan*/  calldata_t ;

/* Variables and functions */
 char* calldata_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sceneitem_rename_hotkey (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void sceneitem_renamed(void *param, calldata_t *data)
{
	obs_sceneitem_t *scene_item = param;
	const char *name = calldata_string(data, "new_name");

	sceneitem_rename_hotkey(scene_item, name);
}