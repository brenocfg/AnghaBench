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
struct op_info {int input_count; double (* func ) (double*,unsigned int) ;scalar_t__ func_all_comps; } ;
struct d3dx_preshader {unsigned int ins_count; int /*<<< orphan*/  regs; struct d3dx_pres_ins* ins; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;
struct d3dx_pres_ins {size_t op; int component_count; TYPE_1__ output; scalar_t__ scalar_op; int /*<<< orphan*/ * inputs; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int ARGS_ARRAY_SIZE ; 
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 double exec_get_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  exec_set_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,double) ; 
 struct op_info* pres_op_info ; 
 double stub1 (double*,unsigned int) ; 
 double stub2 (double*,unsigned int) ; 

__attribute__((used)) static HRESULT execute_preshader(struct d3dx_preshader *pres)
{
    unsigned int i, j, k;
    double args[ARGS_ARRAY_SIZE];
    double res;

    for (i = 0; i < pres->ins_count; ++i)
    {
        const struct d3dx_pres_ins *ins;
        const struct op_info *oi;

        ins = &pres->ins[i];
        oi = &pres_op_info[ins->op];
        if (oi->func_all_comps)
        {
            if (oi->input_count * ins->component_count > ARGS_ARRAY_SIZE)
            {
                FIXME("Too many arguments (%u) for one instruction.\n", oi->input_count * ins->component_count);
                return E_FAIL;
            }
            for (k = 0; k < oi->input_count; ++k)
                for (j = 0; j < ins->component_count; ++j)
                    args[k * ins->component_count + j] = exec_get_arg(&pres->regs, &ins->inputs[k],
                            ins->scalar_op && !k ? 0 : j);
            res = oi->func(args, ins->component_count);

            /* only 'dot' instruction currently falls here */
            exec_set_arg(&pres->regs, &ins->output.reg, 0, res);
        }
        else
        {
            for (j = 0; j < ins->component_count; ++j)
            {
                for (k = 0; k < oi->input_count; ++k)
                    args[k] = exec_get_arg(&pres->regs, &ins->inputs[k], ins->scalar_op && !k ? 0 : j);
                res = oi->func(args, ins->component_count);
                exec_set_arg(&pres->regs, &ins->output.reg, j, res);
            }
        }
    }
    return D3D_OK;
}