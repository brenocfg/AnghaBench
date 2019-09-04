#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_12__ {int /*<<< orphan*/  output_flags; } ;
struct TYPE_13__ {int /*<<< orphan*/  filter_texrender; int /*<<< orphan*/  allow_direct; TYPE_1__ info; } ;
typedef  TYPE_2__ obs_source_t ;
typedef  int /*<<< orphan*/  gs_texture_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 scalar_t__ can_bypass (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gs_texrender_get_texture (int /*<<< orphan*/ ) ; 
 TYPE_2__* obs_filter_get_parent (TYPE_2__*) ; 
 TYPE_2__* obs_filter_get_target (TYPE_2__*) ; 
 int /*<<< orphan*/  obs_ptr_valid (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  render_filter_bypass (TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  render_filter_tex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void obs_source_process_filter_end(obs_source_t *filter, gs_effect_t *effect,
		uint32_t width, uint32_t height)
{
	obs_source_t *target, *parent;
	gs_texture_t *texture;
	uint32_t     parent_flags;

	if (!obs_ptr_valid(filter, "obs_source_process_filter_end"))
		return;

	target       = obs_filter_get_target(filter);
	parent       = obs_filter_get_parent(filter);
	parent_flags = parent->info.output_flags;

	if (can_bypass(target, parent, parent_flags, filter->allow_direct)) {
		render_filter_bypass(target, effect, "Draw");
	} else {
		texture = gs_texrender_get_texture(filter->filter_texrender);
		if (texture)
			render_filter_tex(texture, effect, width, height,
					"Draw");
	}
}