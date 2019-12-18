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
struct gs_effect_param {int /*<<< orphan*/  name; TYPE_1__ annotations; } ;
typedef  struct gs_effect_param gs_eparam_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

gs_eparam_t *gs_param_get_annotation_by_name(const gs_eparam_t *param,
					     const char *name)
{
	if (!param)
		return NULL;
	struct gs_effect_param *params = param->annotations.array;

	for (size_t i = 0; i < param->annotations.num; i++) {
		struct gs_effect_param *g_param = params + i;
		if (strcmp(g_param->name, name) == 0)
			return g_param;
	}
	return NULL;
}