#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct vec3 {scalar_t__ x; scalar_t__ y; } ;
struct vec2 {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_5__ {struct TYPE_5__* next; struct vec2 pos; int /*<<< orphan*/  box_transform; } ;
typedef  TYPE_1__ obs_sceneitem_t ;
struct TYPE_6__ {void* cy; void* cx; TYPE_1__* first_item; } ;
typedef  TYPE_2__ obs_scene_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_INFINITE ; 
 scalar_t__ ceilf (scalar_t__) ; 
 int /*<<< orphan*/  update_item_transform (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vec2_set (struct vec2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec2_sub (struct vec2*,struct vec2*,struct vec2*) ; 
 int /*<<< orphan*/  vec3_set (struct vec3*,float,float,float) ; 
 int /*<<< orphan*/  vec3_transform (struct vec3*,struct vec3*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool resize_scene_base(obs_scene_t *scene,
		struct vec2 *minv,
		struct vec2 *maxv,
		struct vec2 *scale)
{
	vec2_set(minv, M_INFINITE, M_INFINITE);
	vec2_set(maxv, -M_INFINITE, -M_INFINITE);

	obs_sceneitem_t *item = scene->first_item;
	if (!item) {
		scene->cx = 0;
		scene->cy = 0;
		return false;
	}

	while (item) {
#define get_min_max(x_val, y_val) \
		do { \
			struct vec3 v; \
			vec3_set(&v, x_val, y_val, 0.0f); \
			vec3_transform(&v, &v, &item->box_transform); \
			if (v.x < minv->x) minv->x = v.x; \
			if (v.y < minv->y) minv->y = v.y; \
			if (v.x > maxv->x) maxv->x = v.x; \
			if (v.y > maxv->y) maxv->y = v.y; \
		} while (false)

		get_min_max(0.0f, 0.0f);
		get_min_max(1.0f, 0.0f);
		get_min_max(0.0f, 1.0f);
		get_min_max(1.0f, 1.0f);
#undef get_min_max

		item = item->next;
	}

	item = scene->first_item;
	while (item) {
		vec2_sub(&item->pos, &item->pos, minv);
		update_item_transform(item, false);
		item = item->next;
	}

	vec2_sub(scale, maxv, minv);
	scene->cx = (uint32_t)ceilf(scale->x);
	scene->cy = (uint32_t)ceilf(scale->y);
	return true;
}