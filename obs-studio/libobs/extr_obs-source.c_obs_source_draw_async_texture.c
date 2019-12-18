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
struct obs_source {int dummy; } ;
typedef  int /*<<< orphan*/  gs_technique_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/  OBS_EFFECT_DEFAULT ; 
 int /*<<< orphan*/ * gs_effect_get_technique (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * gs_get_effect () ; 
 int /*<<< orphan*/  gs_technique_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_begin_pass (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_technique_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_end_pass (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * obs_get_base_effect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  obs_source_draw_texture (struct obs_source*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void obs_source_draw_async_texture(struct obs_source *source)
{
	gs_effect_t *effect = gs_get_effect();
	bool def_draw = (!effect);
	gs_technique_t *tech = NULL;

	if (def_draw) {
		effect = obs_get_base_effect(OBS_EFFECT_DEFAULT);
		tech = gs_effect_get_technique(effect, "Draw");
		gs_technique_begin(tech);
		gs_technique_begin_pass(tech, 0);
	}

	obs_source_draw_texture(source, effect);

	if (def_draw) {
		gs_technique_end_pass(tech);
		gs_technique_end(tech);
	}
}