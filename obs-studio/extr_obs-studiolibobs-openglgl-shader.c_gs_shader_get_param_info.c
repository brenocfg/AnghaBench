#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gs_shader_param_info {int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ gs_sparam_t ;

/* Variables and functions */

void gs_shader_get_param_info(const gs_sparam_t *param,
		struct gs_shader_param_info *info)
{
	info->type = param->type;
	info->name = param->name;
}