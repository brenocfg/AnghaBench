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
struct gs_effect_param_info {int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ gs_eparam_t ;

/* Variables and functions */

void gs_effect_get_param_info(const gs_eparam_t *param,
		struct gs_effect_param_info *info)
{
	if (!param)
		return;

	info->name = param->name;
	info->type = param->type;
}