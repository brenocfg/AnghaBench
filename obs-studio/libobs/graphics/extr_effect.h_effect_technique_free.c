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
struct TYPE_2__ {size_t num; scalar_t__ array; } ;
struct gs_effect_technique {int /*<<< orphan*/  name; TYPE_1__ passes; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 
 int /*<<< orphan*/  effect_pass_free (scalar_t__) ; 

__attribute__((used)) static inline void effect_technique_free(struct gs_effect_technique *t)
{
	size_t i;
	for (i = 0; i < t->passes.num; i++)
		effect_pass_free(t->passes.array + i);

	da_free(t->passes);
	bfree(t->name);
}