#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  num; int /*<<< orphan*/  array; } ;
struct TYPE_6__ {TYPE_1__ def_value; } ;
typedef  TYPE_2__ gs_sparam_t ;

/* Variables and functions */
 int /*<<< orphan*/  gs_shader_set_val (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void gs_shader_set_default(gs_sparam_t *param)
{
	gs_shader_set_val(param, param->def_value.array, param->def_value.num);
}