#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pass_shaderparam {int /*<<< orphan*/ * sparam; struct gs_effect_param* eparam; } ;
struct TYPE_3__ {int /*<<< orphan*/  num; int /*<<< orphan*/  array; } ;
struct TYPE_4__ {scalar_t__ num; } ;
struct gs_effect_param {TYPE_1__ cur_val; TYPE_2__ default_val; int /*<<< orphan*/  changed; scalar_t__ next_sampler; } ;
struct darray {size_t num; struct pass_shaderparam* array; } ;
typedef  int /*<<< orphan*/  gs_sparam_t ;

/* Variables and functions */
 int /*<<< orphan*/  da_copy (TYPE_1__,TYPE_2__) ; 
 int /*<<< orphan*/  gs_shader_set_next_sampler (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  gs_shader_set_val (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void upload_shader_params(struct darray *pass_params, bool changed_only)
{
	struct pass_shaderparam *params = pass_params->array;
	size_t i;

	for (i = 0; i < pass_params->num; i++) {
		struct pass_shaderparam *param = params + i;
		struct gs_effect_param *eparam = param->eparam;
		gs_sparam_t *sparam = param->sparam;

		if (eparam->next_sampler)
			gs_shader_set_next_sampler(sparam,
						   eparam->next_sampler);

		if (changed_only && !eparam->changed)
			continue;

		if (!eparam->cur_val.num) {
			if (eparam->default_val.num)
				da_copy(eparam->cur_val, eparam->default_val);
			else
				continue;
		}

		gs_shader_set_val(sparam, eparam->cur_val.array,
				  eparam->cur_val.num);
	}
}