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
typedef  int /*<<< orphan*/  gs_eparam_t ;
typedef  int /*<<< orphan*/  gs_effect_t ;

/* Variables and functions */
 int /*<<< orphan*/ * gs_effect_get_param_by_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  gs_effect_set_float (int /*<<< orphan*/ *,float) ; 

__attribute__((used)) static inline void set_eparam(gs_effect_t *effect, const char *name, float val)
{
	gs_eparam_t *param = gs_effect_get_param_by_name(effect, name);
	gs_effect_set_float(param, val);
}