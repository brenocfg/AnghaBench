#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ data; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* video_render ) (scalar_t__,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {TYPE_3__ context; TYPE_1__ info; } ;
typedef  TYPE_4__ obs_source_t ;
typedef  int /*<<< orphan*/  gs_technique_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;
struct TYPE_8__ {int /*<<< orphan*/ * default_effect; } ;
struct TYPE_11__ {TYPE_2__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/ * gs_effect_get_technique (int /*<<< orphan*/ *,char*) ; 
 size_t gs_technique_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_begin_pass (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  gs_technique_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_technique_end_pass (int /*<<< orphan*/ *) ; 
 TYPE_6__* obs ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ *) ; 

void obs_source_default_render(obs_source_t *source)
{
	gs_effect_t *effect = obs->video.default_effect;
	gs_technique_t *tech = gs_effect_get_technique(effect, "Draw");
	size_t passes, i;

	passes = gs_technique_begin(tech);
	for (i = 0; i < passes; i++) {
		gs_technique_begin_pass(tech, i);
		if (source->context.data)
			source->info.video_render(source->context.data, effect);
		gs_technique_end_pass(tech);
	}
	gs_technique_end(tech);
}