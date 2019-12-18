#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ (* walk_parameter_dep_func ) (void*,struct d3dx_parameter*) ;
struct d3dx_sampler {unsigned int state_count; int /*<<< orphan*/ * states; } ;
struct d3dx_parameter {scalar_t__ class; unsigned int element_count; unsigned int member_count; TYPE_2__* members; struct d3dx_sampler* data; int /*<<< orphan*/  type; int /*<<< orphan*/  param_eval; TYPE_1__* top_level_param; } ;
struct TYPE_4__ {int /*<<< orphan*/  param_eval; struct d3dx_sampler* data; } ;
struct TYPE_3__ {struct d3dx_parameter param; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ D3DXPC_OBJECT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ is_param_type_sampler (int /*<<< orphan*/ ) ; 
 unsigned int max (unsigned int,int) ; 
 scalar_t__ walk_param_eval_dep (int /*<<< orphan*/ ,scalar_t__ (*) (void*,struct d3dx_parameter*),void*) ; 
 scalar_t__ walk_state_dep (int /*<<< orphan*/ *,scalar_t__ (*) (void*,struct d3dx_parameter*),void*) ; 

__attribute__((used)) static BOOL walk_parameter_dep(struct d3dx_parameter *param, walk_parameter_dep_func param_func,
        void *data)
{
    unsigned int i;
    unsigned int member_count;

    param = &param->top_level_param->param;
    if (param_func(data, param))
        return TRUE;

    if (walk_param_eval_dep(param->param_eval, param_func, data))
        return TRUE;

    if (param->class == D3DXPC_OBJECT && is_param_type_sampler(param->type))
    {
        struct d3dx_sampler *sampler;
        unsigned int sampler_idx;
        unsigned int samplers_count = max(param->element_count, 1);

        for (sampler_idx = 0; sampler_idx < samplers_count; ++sampler_idx)
        {
            sampler = param->element_count ? param->members[sampler_idx].data : param->data;
            for (i = 0; i < sampler->state_count; ++i)
            {
                if (walk_state_dep(&sampler->states[i], param_func, data))
                    return TRUE;
            }
        }
        return FALSE;
    }

    member_count = param->element_count ? param->element_count : param->member_count;
    for (i = 0; i < member_count; ++i)
    {
        if (walk_param_eval_dep(param->members[i].param_eval, param_func, data))
            return TRUE;
    }

    return FALSE;
}