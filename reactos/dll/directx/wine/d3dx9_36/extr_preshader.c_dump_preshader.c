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
struct TYPE_2__ {int* table_sizes; double** tables; } ;
struct d3dx_preshader {unsigned int ins_count; int /*<<< orphan*/ * ins; TYPE_1__ regs; int /*<<< orphan*/  inputs; } ;

/* Variables and functions */
 size_t PRES_REGTAB_IMMED ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  dump_ins (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_registers (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dump_preshader(struct d3dx_preshader *pres)
{
    unsigned int i, immediate_count = pres->regs.table_sizes[PRES_REGTAB_IMMED] * 4;
    const double *immediates = pres->regs.tables[PRES_REGTAB_IMMED];

    if (immediate_count)
        TRACE("// Immediates:\n");
    for (i = 0; i < immediate_count; ++i)
    {
        if (!(i % 4))
            TRACE("// ");
        TRACE("%.8e", immediates[i]);
        if (i % 4 == 3)
            TRACE("\n");
        else
            TRACE(", ");
    }
    TRACE("// Preshader registers:\n");
    dump_registers(&pres->inputs);
    TRACE("preshader\n");
    for (i = 0; i < pres->ins_count; ++i)
        dump_ins(&pres->regs, &pres->ins[i]);
}