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
struct gs_effect_pass {int dummy; } ;
struct TYPE_4__ {size_t num; struct gs_effect_pass* array; } ;
struct TYPE_5__ {TYPE_1__ passes; } ;
typedef  TYPE_2__ gs_technique_t ;
typedef  struct gs_effect_pass gs_epass_t ;

/* Variables and functions */

gs_epass_t *gs_technique_get_pass_by_idx(const gs_technique_t *technique,
		size_t pass)
{
	if (!technique) return NULL;
	struct gs_effect_pass *passes = technique->passes.array;

	if (pass > technique->passes.num)
		return NULL;

	return passes + pass;
}