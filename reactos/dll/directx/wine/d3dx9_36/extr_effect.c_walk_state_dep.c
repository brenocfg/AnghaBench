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
typedef  int /*<<< orphan*/  walk_parameter_dep_func ;
struct TYPE_2__ {int /*<<< orphan*/  param_eval; int /*<<< orphan*/  type; } ;
struct d3dx_state {scalar_t__ type; TYPE_1__ parameter; TYPE_1__* referenced_param; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ST_ARRAY_SELECTOR ; 
 scalar_t__ ST_CONSTANT ; 
 scalar_t__ ST_PARAMETER ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ is_param_type_sampler (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  walk_param_eval_dep (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ walk_parameter_dep (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static BOOL walk_state_dep(struct d3dx_state *state, walk_parameter_dep_func param_func,
        void *data)
{
    if (state->type == ST_CONSTANT && is_param_type_sampler(state->parameter.type))
    {
        if (walk_parameter_dep(&state->parameter, param_func, data))
            return TRUE;
    }
    else if (state->type == ST_ARRAY_SELECTOR || state->type == ST_PARAMETER)
    {
        if (walk_parameter_dep(state->referenced_param, param_func, data))
            return TRUE;
    }
    return walk_param_eval_dep(state->parameter.param_eval, param_func, data);
}