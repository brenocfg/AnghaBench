#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct obs_scene_item {TYPE_1__* parent; TYPE_3__* prev; TYPE_2__* next; } ;
struct TYPE_6__ {TYPE_2__* next; } ;
struct TYPE_5__ {TYPE_3__* prev; } ;
struct TYPE_4__ {TYPE_2__* first_item; } ;

/* Variables and functions */

__attribute__((used)) static inline void detach_sceneitem(struct obs_scene_item *item)
{
	if (item->prev)
		item->prev->next = item->next;
	else
		item->parent->first_item = item->next;

	if (item->next)
		item->next->prev = item->prev;

	item->parent = NULL;
}