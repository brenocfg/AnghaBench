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
struct d3dx_param_eval {int /*<<< orphan*/  shader_inputs; int /*<<< orphan*/  pres; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct d3dx_param_eval*) ; 
 int /*<<< orphan*/  TRACE (char*,struct d3dx_param_eval*) ; 
 int /*<<< orphan*/  d3dx_free_const_tab (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d3dx_free_preshader (int /*<<< orphan*/ *) ; 

void d3dx_free_param_eval(struct d3dx_param_eval *peval)
{
    TRACE("peval %p.\n", peval);

    if (!peval)
        return;

    d3dx_free_preshader(&peval->pres);
    d3dx_free_const_tab(&peval->shader_inputs);
    HeapFree(GetProcessHeap(), 0, peval);
}