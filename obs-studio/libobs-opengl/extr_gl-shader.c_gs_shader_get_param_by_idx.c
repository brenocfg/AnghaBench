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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  gs_sparam_t ;
struct TYPE_4__ {scalar_t__ num; int /*<<< orphan*/ * array; } ;
struct TYPE_5__ {TYPE_1__ params; } ;
typedef  TYPE_2__ gs_shader_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

gs_sparam_t *gs_shader_get_param_by_idx(gs_shader_t *shader, uint32_t param)
{
	assert(param < shader->params.num);
	return shader->params.array + param;
}