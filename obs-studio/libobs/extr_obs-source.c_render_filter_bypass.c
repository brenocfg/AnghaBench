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
typedef  int /*<<< orphan*/  obs_source_t ;
typedef  int /*<<< orphan*/  gs_technique_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/ * gs_effect_get_technique (int /*<<< orphan*/ *,char const*) ; 
 size_t gs_technique_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_begin_pass (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  gs_technique_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_end_pass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  obs_source_video_render (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void render_filter_bypass(obs_source_t *target,
					gs_effect_t *effect,
					const char *tech_name)
{
	gs_technique_t *tech = gs_effect_get_technique(effect, tech_name);
	size_t passes, i;

	passes = gs_technique_begin(tech);
	for (i = 0; i < passes; i++) {
		gs_technique_begin_pass(tech, i);
		obs_source_video_render(target);
		gs_technique_end_pass(tech);
	}
	gs_technique_end(tech);
}