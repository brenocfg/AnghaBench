#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct gs_effect_param {int changed; int /*<<< orphan*/ * next_sampler; int /*<<< orphan*/  cur_val; } ;
struct TYPE_6__ {size_t num; struct gs_effect_param* array; } ;
struct gs_effect {TYPE_2__ params; TYPE_1__* graphics; int /*<<< orphan*/ * cur_technique; } ;
struct TYPE_7__ {struct gs_effect* effect; } ;
typedef  TYPE_3__ gs_technique_t ;
struct TYPE_5__ {int /*<<< orphan*/ * cur_effect; } ;

/* Variables and functions */
 int /*<<< orphan*/  da_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_load_pixelshader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gs_load_vertexshader (int /*<<< orphan*/ *) ; 

void gs_technique_end(gs_technique_t *tech)
{
	if (!tech)
		return;

	struct gs_effect *effect = tech->effect;
	struct gs_effect_param *params = effect->params.array;
	size_t i;

	gs_load_vertexshader(NULL);
	gs_load_pixelshader(NULL);

	tech->effect->cur_technique = NULL;
	tech->effect->graphics->cur_effect = NULL;

	for (i = 0; i < effect->params.num; i++) {
		struct gs_effect_param *param = params + i;

		da_free(param->cur_val);
		param->changed = false;
		if (param->next_sampler)
			param->next_sampler = NULL;
	}
}