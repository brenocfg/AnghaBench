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
struct shader_var {int /*<<< orphan*/  default_val; int /*<<< orphan*/  gl_sampler_id; int /*<<< orphan*/  type; int /*<<< orphan*/  name; int /*<<< orphan*/  array_count; } ;
struct gs_shader_param {scalar_t__ type; int changed; int /*<<< orphan*/  def_value; int /*<<< orphan*/  cur_value; scalar_t__ texture_id; int /*<<< orphan*/  sampler_id; struct gs_shader* shader; int /*<<< orphan*/  name; int /*<<< orphan*/  array_count; int /*<<< orphan*/  member_0; } ;
struct gs_shader {int /*<<< orphan*/  params; } ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 scalar_t__ GS_SHADER_PARAM_TEXTURE ; 
 int /*<<< orphan*/  bstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_push_back (int /*<<< orphan*/ ,struct gs_shader_param*) ; 
 scalar_t__ get_shader_param_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gl_add_param(struct gs_shader *shader, struct shader_var *var,
			 GLint *texture_id)
{
	struct gs_shader_param param = {0};

	param.array_count = var->array_count;
	param.name = bstrdup(var->name);
	param.shader = shader;
	param.type = get_shader_param_type(var->type);

	if (param.type == GS_SHADER_PARAM_TEXTURE) {
		param.sampler_id = var->gl_sampler_id;
		param.texture_id = (*texture_id)++;
	} else {
		param.changed = true;
	}

	da_move(param.def_value, var->default_val);
	da_copy(param.cur_value, param.def_value);

	da_push_back(shader->params, &param);
	return true;
}