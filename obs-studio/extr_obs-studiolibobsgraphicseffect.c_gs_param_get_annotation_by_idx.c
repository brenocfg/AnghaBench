#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t num; struct gs_effect_param* array; } ;
struct gs_effect_param {TYPE_1__ annotations; } ;
typedef  struct gs_effect_param gs_eparam_t ;

/* Variables and functions */

gs_eparam_t *gs_param_get_annotation_by_idx(const gs_eparam_t *param,
		size_t annotation)
{
	if (!param) return NULL;
	
	struct gs_effect_param *params = param->annotations.array;
	if (annotation > param->annotations.num)
		return NULL;

	return params + annotation;
}