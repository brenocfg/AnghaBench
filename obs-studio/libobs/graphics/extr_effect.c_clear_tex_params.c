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
struct pass_shaderparam {int /*<<< orphan*/  sparam; } ;
struct gs_shader_param_info {scalar_t__ type; } ;
struct darray {size_t num; struct pass_shaderparam* array; } ;

/* Variables and functions */
 scalar_t__ GS_SHADER_PARAM_TEXTURE ; 
 int /*<<< orphan*/  gs_shader_get_param_info (int /*<<< orphan*/ ,struct gs_shader_param_info*) ; 
 int /*<<< orphan*/  gs_shader_set_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void clear_tex_params(struct darray *in_params)
{
	struct pass_shaderparam *params = in_params->array;

	for (size_t i = 0; i < in_params->num; i++) {
		struct pass_shaderparam *param = params + i;
		struct gs_shader_param_info info;

		gs_shader_get_param_info(param->sparam, &info);
		if (info.type == GS_SHADER_PARAM_TEXTURE)
			gs_shader_set_texture(param->sparam, NULL);
	}
}