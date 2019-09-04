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
struct gs_effect {struct gs_effect* next; int /*<<< orphan*/  effect_path; } ;
struct TYPE_2__ {struct gs_effect* first_effect; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* thread_graphics ; 

__attribute__((used)) static inline struct gs_effect *find_cached_effect(const char *filename)
{
	struct gs_effect *effect = thread_graphics->first_effect;

	while (effect) {
		if (strcmp(effect->effect_path, filename) == 0)
			break;
		effect = effect->next;
	}

	return effect;
}