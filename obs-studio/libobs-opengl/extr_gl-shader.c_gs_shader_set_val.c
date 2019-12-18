#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  gs_texture_t ;
struct TYPE_4__ {int array_count; int const type; int /*<<< orphan*/  cur_value; } ;
typedef  TYPE_1__ gs_sparam_t ;

/* Variables and functions */
#define  GS_SHADER_PARAM_BOOL 138 
#define  GS_SHADER_PARAM_FLOAT 137 
#define  GS_SHADER_PARAM_INT 136 
#define  GS_SHADER_PARAM_INT2 135 
#define  GS_SHADER_PARAM_INT3 134 
#define  GS_SHADER_PARAM_INT4 133 
#define  GS_SHADER_PARAM_MATRIX4X4 132 
#define  GS_SHADER_PARAM_TEXTURE 131 
#define  GS_SHADER_PARAM_VEC2 130 
#define  GS_SHADER_PARAM_VEC3 129 
#define  GS_SHADER_PARAM_VEC4 128 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  da_copy_array (int /*<<< orphan*/ ,void const*,size_t) ; 
 int /*<<< orphan*/  gs_shader_set_texture (TYPE_1__*,int /*<<< orphan*/ *) ; 

void gs_shader_set_val(gs_sparam_t *param, const void *val, size_t size)
{
	int count = param->array_count;
	size_t expected_size = 0;
	if (!count)
		count = 1;

	switch ((uint32_t)param->type) {
	case GS_SHADER_PARAM_FLOAT:
		expected_size = sizeof(float);
		break;
	case GS_SHADER_PARAM_BOOL:
	case GS_SHADER_PARAM_INT:
		expected_size = sizeof(int);
		break;
	case GS_SHADER_PARAM_INT2:
		expected_size = sizeof(int) * 2;
		break;
	case GS_SHADER_PARAM_INT3:
		expected_size = sizeof(int) * 3;
		break;
	case GS_SHADER_PARAM_INT4:
		expected_size = sizeof(int) * 4;
		break;
	case GS_SHADER_PARAM_VEC2:
		expected_size = sizeof(float) * 2;
		break;
	case GS_SHADER_PARAM_VEC3:
		expected_size = sizeof(float) * 3;
		break;
	case GS_SHADER_PARAM_VEC4:
		expected_size = sizeof(float) * 4;
		break;
	case GS_SHADER_PARAM_MATRIX4X4:
		expected_size = sizeof(float) * 4 * 4;
		break;
	case GS_SHADER_PARAM_TEXTURE:
		expected_size = sizeof(void *);
		break;
	default:
		expected_size = 0;
	}

	expected_size *= count;
	if (!expected_size)
		return;

	if (expected_size != size) {
		blog(LOG_ERROR, "gs_shader_set_val (GL): Size of shader "
				"param does not match the size of the input");
		return;
	}

	if (param->type == GS_SHADER_PARAM_TEXTURE)
		gs_shader_set_texture(param, *(gs_texture_t **)val);
	else
		da_copy_array(param->cur_value, val, size);
}