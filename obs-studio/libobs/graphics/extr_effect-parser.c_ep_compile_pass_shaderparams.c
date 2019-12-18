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
struct pass_shaderparam {int /*<<< orphan*/  sparam; int /*<<< orphan*/  eparam; } ;
struct effect_parser {int /*<<< orphan*/  effect; } ;
struct dstr {int /*<<< orphan*/  array; } ;
struct darray {size_t num; } ;
typedef  int /*<<< orphan*/  gs_shader_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 void* darray_item (int,struct darray*,size_t) ; 
 int /*<<< orphan*/  darray_resize (int,struct darray*,size_t) ; 
 int /*<<< orphan*/  debug_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*) ; 
 int /*<<< orphan*/  gs_effect_get_param_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gs_shader_get_param_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ep_compile_pass_shaderparams(struct effect_parser *ep,
					 struct darray *pass_params,
					 struct darray *used_params,
					 gs_shader_t *shader)
{
	size_t i;
	darray_resize(sizeof(struct pass_shaderparam), pass_params,
		      used_params->num);

	for (i = 0; i < pass_params->num; i++) {
		struct dstr *param_name;
		struct pass_shaderparam *param;

		param_name = darray_item(sizeof(struct dstr), used_params, i);
		param = darray_item(sizeof(struct pass_shaderparam),
				    pass_params, i);

		param->eparam = gs_effect_get_param_by_name(ep->effect,
							    param_name->array);
		param->sparam =
			gs_shader_get_param_by_name(shader, param_name->array);

#if defined(_DEBUG) && defined(_DEBUG_SHADERS)
		debug_param(param->eparam, 0, i, "\t\t\t\t");
#endif

		if (!param->sparam) {
			blog(LOG_ERROR, "Effect shader parameter not found");
			return false;
		}
	}

	return true;
}