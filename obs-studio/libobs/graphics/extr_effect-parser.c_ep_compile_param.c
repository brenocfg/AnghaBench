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
struct gs_effect_param {int /*<<< orphan*/  type; int /*<<< orphan*/  default_val; TYPE_3__* effect; int /*<<< orphan*/  section; int /*<<< orphan*/  name; } ;
struct ep_param {int /*<<< orphan*/  name; int /*<<< orphan*/  type; int /*<<< orphan*/  default_val; struct gs_effect_param* param; } ;
struct TYPE_5__ {struct ep_param* array; } ;
struct effect_parser {TYPE_3__* effect; TYPE_2__ params; } ;
struct TYPE_4__ {struct gs_effect_param* array; } ;
struct TYPE_6__ {struct gs_effect_param* world; struct gs_effect_param* view_proj; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFFECT_PARAM ; 
 int /*<<< orphan*/  bstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_param (struct gs_effect_param*,struct ep_param*,size_t,char*) ; 
 int /*<<< orphan*/  ep_compile_param_annotations (struct ep_param*,struct gs_effect_param*,struct effect_parser*) ; 
 int /*<<< orphan*/  get_effect_param_type (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ep_compile_param(struct effect_parser *ep, size_t idx)
{
	struct gs_effect_param *param;
	struct ep_param *param_in;

	param = ep->effect->params.array + idx;
	param_in = ep->params.array + idx;
	param_in->param = param;

	param->name = bstrdup(param_in->name);
	param->section = EFFECT_PARAM;
	param->effect = ep->effect;
	da_move(param->default_val, param_in->default_val);

	param->type = get_effect_param_type(param_in->type);

	if (strcmp(param_in->name, "ViewProj") == 0)
		ep->effect->view_proj = param;
	else if (strcmp(param_in->name, "World") == 0)
		ep->effect->world = param;

#if defined(_DEBUG) && defined(_DEBUG_SHADERS)
	debug_param(param, param_in, idx, "\t");
#endif

	ep_compile_param_annotations(param_in, param, ep);
}