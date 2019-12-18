#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct vec2 {float x; float y; } ;
struct matrix4 {int dummy; } ;
struct TYPE_9__ {int transition_scale_type; int /*<<< orphan*/ * transition_matrices; int /*<<< orphan*/  transition_alignment; struct TYPE_9__** transition_sources; } ;
typedef  TYPE_1__ obs_source_t ;
typedef  enum obs_transition_scale_type { ____Placeholder_obs_transition_scale_type } obs_transition_scale_type ;

/* Variables and functions */
 int OBS_TRANSITION_SCALE_ASPECT ; 
 int OBS_TRANSITION_SCALE_MAX_ONLY ; 
 int OBS_TRANSITION_SCALE_STRETCH ; 
 int /*<<< orphan*/  add_alignment (struct vec2*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ get_cx (TYPE_1__*) ; 
 scalar_t__ get_cy (TYPE_1__*) ; 
 int /*<<< orphan*/  lock_transition (TYPE_1__*) ; 
 int /*<<< orphan*/  matrix4_copy (int /*<<< orphan*/ *,struct matrix4*) ; 
 int /*<<< orphan*/  matrix4_identity (struct matrix4*) ; 
 int /*<<< orphan*/  matrix4_scale3f (struct matrix4*,struct matrix4*,float,float,float) ; 
 int /*<<< orphan*/  matrix4_translate3f (struct matrix4*,struct matrix4*,float,float,float) ; 
 scalar_t__ obs_source_get_height (TYPE_1__*) ; 
 scalar_t__ obs_source_get_width (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock_transition (TYPE_1__*) ; 
 int /*<<< orphan*/  vec2_zero (struct vec2*) ; 

__attribute__((used)) static void recalculate_transition_matrix(obs_source_t *tr, size_t idx)
{
	obs_source_t *child;
	struct matrix4 mat;
	struct vec2 pos;
	struct vec2 scale;
	float tr_cx = (float)get_cx(tr);
	float tr_cy = (float)get_cy(tr);
	float source_cx;
	float source_cy;
	float tr_aspect = tr_cx / tr_cy;
	float source_aspect;
	enum obs_transition_scale_type scale_type = tr->transition_scale_type;

	lock_transition(tr);

	child = tr->transition_sources[idx];
	if (!child) {
		unlock_transition(tr);
		return;
	}

	source_cx = (float)obs_source_get_width(child);
	source_cy = (float)obs_source_get_height(child);
	unlock_transition(tr);

	if (source_cx == 0.0f || source_cy == 0.0f)
		return;

	source_aspect = source_cx / source_cy;

	if (scale_type == OBS_TRANSITION_SCALE_MAX_ONLY) {
		if (source_cx > tr_cx || source_cy > tr_cy) {
			scale_type = OBS_TRANSITION_SCALE_ASPECT;
		} else {
			scale.x = 1.0f;
			scale.y = 1.0f;
		}
	}

	if (scale_type == OBS_TRANSITION_SCALE_ASPECT) {
		bool use_width = tr_aspect < source_aspect;
		scale.x = scale.y = use_width ? tr_cx / source_cx
					      : tr_cy / source_cy;

	} else if (scale_type == OBS_TRANSITION_SCALE_STRETCH) {
		scale.x = tr_cx / source_cx;
		scale.y = tr_cy / source_cy;
	}

	source_cx *= scale.x;
	source_cy *= scale.y;

	vec2_zero(&pos);
	add_alignment(&pos, tr->transition_alignment, (int)(tr_cx - source_cx),
		      (int)(tr_cy - source_cy));

	matrix4_identity(&mat);
	matrix4_scale3f(&mat, &mat, scale.x, scale.y, 1.0f);
	matrix4_translate3f(&mat, &mat, pos.x, pos.y, 0.0f);
	matrix4_copy(&tr->transition_matrices[idx], &mat);
}