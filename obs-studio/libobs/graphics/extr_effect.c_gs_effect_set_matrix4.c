#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct matrix4 {int dummy; } ;
typedef  int /*<<< orphan*/  gs_eparam_t ;

/* Variables and functions */
 int /*<<< orphan*/  effect_setval_inline (int /*<<< orphan*/ *,struct matrix4 const*,int) ; 

void gs_effect_set_matrix4(gs_eparam_t *param, const struct matrix4 *val)
{
	effect_setval_inline(param, val, sizeof(struct matrix4));
}