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
typedef  int /*<<< orphan*/  int_val ;
struct TYPE_3__ {int /*<<< orphan*/  cur_value; } ;
typedef  TYPE_1__ gs_sparam_t ;

/* Variables and functions */
 int /*<<< orphan*/  da_copy_array (int /*<<< orphan*/ ,int*,int) ; 

void gs_shader_set_bool(gs_sparam_t *param, bool val)
{
	int int_val = val;
	da_copy_array(param->cur_value, &int_val, sizeof(int_val));
}