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
struct gs_effect_param {TYPE_1__ annotations; TYPE_1__ default_val; TYPE_1__ cur_val; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da_free (TYPE_1__) ; 

__attribute__((used)) static inline void effect_param_free(struct gs_effect_param *param)
{
	bfree(param->name);
	//bfree(param->full_name);
	da_free(param->cur_val);
	da_free(param->default_val);

	size_t i;
	for (i = 0; i < param->annotations.num; i++)
		effect_param_free(param->annotations.array + i);

	da_free(param->annotations);
}