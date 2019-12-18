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
struct obs_scene_item {int removed; } ;

/* Variables and functions */
 int /*<<< orphan*/  detach_sceneitem (struct obs_scene_item*) ; 
 int /*<<< orphan*/  set_visibility (struct obs_scene_item*,int) ; 
 int /*<<< orphan*/  signal_item_remove (struct obs_scene_item*) ; 

__attribute__((used)) static inline void remove_without_release(struct obs_scene_item *item)
{
	item->removed = true;
	set_visibility(item, false);
	signal_item_remove(item);
	detach_sceneitem(item);
}