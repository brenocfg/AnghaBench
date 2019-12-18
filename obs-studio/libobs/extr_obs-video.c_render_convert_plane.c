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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  gs_technique_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  GS_TRIS ; 
 int /*<<< orphan*/  gs_draw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gs_effect_get_technique (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  gs_set_render_target (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t gs_technique_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_begin_pass (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  gs_technique_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_end_pass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_texture_get_height (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_texture_get_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_render_size (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void render_convert_plane(gs_effect_t *effect, gs_texture_t *target,
				 const char *tech_name)
{
	gs_technique_t *tech = gs_effect_get_technique(effect, tech_name);

	const uint32_t width = gs_texture_get_width(target);
	const uint32_t height = gs_texture_get_height(target);

	gs_set_render_target(target, NULL);
	set_render_size(width, height);

	size_t passes = gs_technique_begin(tech);
	for (size_t i = 0; i < passes; i++) {
		gs_technique_begin_pass(tech, i);
		gs_draw(GS_TRIS, 0, 3);
		gs_technique_end_pass(tech);
	}
	gs_technique_end(tech);
}