#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct vec4 {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * transition_texrender; int /*<<< orphan*/ * transition_matrices; } ;
typedef  TYPE_1__ obs_source_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_CLEAR_COLOR ; 
 scalar_t__ get_cx (TYPE_1__*) ; 
 scalar_t__ get_cy (TYPE_1__*) ; 
 int /*<<< orphan*/  gs_clear (int /*<<< orphan*/ ,struct vec4*,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_matrix_mul (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_matrix_pop () ; 
 int /*<<< orphan*/  gs_matrix_push () ; 
 int /*<<< orphan*/  gs_ortho (float,float,float,float,float,float) ; 
 scalar_t__ gs_texrender_begin (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gs_texrender_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_video_render (TYPE_1__*) ; 
 int /*<<< orphan*/  vec4_zero (struct vec4*) ; 

__attribute__((used)) static inline void render_child(obs_source_t *transition, obs_source_t *child,
				size_t idx)
{
	uint32_t cx = get_cx(transition);
	uint32_t cy = get_cy(transition);
	struct vec4 blank;
	if (!child)
		return;

	if (gs_texrender_begin(transition->transition_texrender[idx], cx, cy)) {
		vec4_zero(&blank);
		gs_clear(GS_CLEAR_COLOR, &blank, 0.0f, 0);
		gs_ortho(0.0f, (float)cx, 0.0f, (float)cy, -100.0f, 100.0f);

		gs_matrix_push();
		gs_matrix_mul(&transition->transition_matrices[idx]);
		obs_source_video_render(child);
		gs_matrix_pop();

		gs_texrender_end(transition->transition_texrender[idx]);
	}
}