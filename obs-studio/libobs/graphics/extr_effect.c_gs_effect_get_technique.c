#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gs_effect_technique {int /*<<< orphan*/  name; } ;
typedef  struct gs_effect_technique gs_technique_t ;
struct TYPE_4__ {size_t num; struct gs_effect_technique* array; } ;
struct TYPE_5__ {TYPE_1__ techniques; } ;
typedef  TYPE_2__ gs_effect_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

gs_technique_t *gs_effect_get_technique(const gs_effect_t *effect,
					const char *name)
{
	if (!effect)
		return NULL;

	for (size_t i = 0; i < effect->techniques.num; i++) {
		struct gs_effect_technique *tech = effect->techniques.array + i;
		if (strcmp(tech->name, name) == 0)
			return tech;
	}

	return NULL;
}