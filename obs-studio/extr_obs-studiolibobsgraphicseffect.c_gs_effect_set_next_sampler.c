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
typedef  int /*<<< orphan*/  gs_samplerstate_t ;
struct TYPE_3__ {scalar_t__ type; int /*<<< orphan*/ * next_sampler; } ;
typedef  TYPE_1__ gs_eparam_t ;

/* Variables and functions */
 scalar_t__ GS_SHADER_PARAM_TEXTURE ; 
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  blog (int /*<<< orphan*/ ,char*) ; 

void gs_effect_set_next_sampler(gs_eparam_t *param, gs_samplerstate_t *sampler)
{
	if (!param) {
		blog(LOG_ERROR, "gs_effect_set_next_sampler: invalid param");
		return;
	}

	if (param->type == GS_SHADER_PARAM_TEXTURE)
		param->next_sampler = sampler;
}