#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct obs_scene_item {int /*<<< orphan*/ * source; struct obs_scene_item* next; } ;
typedef  int /*<<< orphan*/  obs_source_t ;
struct TYPE_3__ {struct obs_scene_item* first_item; } ;
typedef  TYPE_1__ obs_scene_t ;

/* Variables and functions */

__attribute__((used)) static obs_source_t *get_child_at_idx(obs_scene_t *scene, size_t idx)
{
	struct obs_scene_item *item = scene->first_item;

	while (item && idx--)
		item = item->next;
	return item ? item->source : NULL;
}