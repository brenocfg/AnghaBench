#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct vec2 {float x; float y; } ;
struct TYPE_2__ {float x; float y; } ;
struct obs_scene_item {scalar_t__ bounds_type; int /*<<< orphan*/  bounds_align; TYPE_1__ bounds; } ;

/* Variables and functions */
 scalar_t__ OBS_BOUNDS_MAX_ONLY ; 
 scalar_t__ OBS_BOUNDS_SCALE_INNER ; 
 scalar_t__ OBS_BOUNDS_SCALE_OUTER ; 
 scalar_t__ OBS_BOUNDS_SCALE_TO_HEIGHT ; 
 scalar_t__ OBS_BOUNDS_SCALE_TO_WIDTH ; 
 scalar_t__ OBS_BOUNDS_STRETCH ; 
 int /*<<< orphan*/  add_alignment (struct vec2*,int /*<<< orphan*/ ,int,int) ; 
 float fabsf (float) ; 
 int /*<<< orphan*/  vec2_mulf (struct vec2*,struct vec2*,float) ; 

__attribute__((used)) static void calculate_bounds_data(struct obs_scene_item *item,
				  struct vec2 *origin, struct vec2 *scale,
				  uint32_t *cx, uint32_t *cy)
{
	float width = (float)(*cx) * fabsf(scale->x);
	float height = (float)(*cy) * fabsf(scale->y);
	float item_aspect = width / height;
	float bounds_aspect = item->bounds.x / item->bounds.y;
	uint32_t bounds_type = item->bounds_type;
	float width_diff, height_diff;

	if (item->bounds_type == OBS_BOUNDS_MAX_ONLY)
		if (width > item->bounds.x || height > item->bounds.y)
			bounds_type = OBS_BOUNDS_SCALE_INNER;

	if (bounds_type == OBS_BOUNDS_SCALE_INNER ||
	    bounds_type == OBS_BOUNDS_SCALE_OUTER) {
		bool use_width = (bounds_aspect < item_aspect);
		float mul;

		if (item->bounds_type == OBS_BOUNDS_SCALE_OUTER)
			use_width = !use_width;

		mul = use_width ? item->bounds.x / width
				: item->bounds.y / height;

		vec2_mulf(scale, scale, mul);

	} else if (bounds_type == OBS_BOUNDS_SCALE_TO_WIDTH) {
		vec2_mulf(scale, scale, item->bounds.x / width);

	} else if (bounds_type == OBS_BOUNDS_SCALE_TO_HEIGHT) {
		vec2_mulf(scale, scale, item->bounds.y / height);

	} else if (bounds_type == OBS_BOUNDS_STRETCH) {
		scale->x = item->bounds.x / (float)(*cx);
		scale->y = item->bounds.y / (float)(*cy);
	}

	width = (float)(*cx) * scale->x;
	height = (float)(*cy) * scale->y;
	width_diff = item->bounds.x - width;
	height_diff = item->bounds.y - height;
	*cx = (uint32_t)item->bounds.x;
	*cy = (uint32_t)item->bounds.y;

	add_alignment(origin, item->bounds_align, (int)-width_diff,
		      (int)-height_diff);
}