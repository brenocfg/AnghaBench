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
struct pevaluator {char* error; int /*<<< orphan*/  values; int /*<<< orphan*/  pool; scalar_t__ stk_index; int /*<<< orphan*/  stack; struct cpu_stack_walk* csw; } ;
struct pdb_cmd_pair {char* name; int /*<<< orphan*/ * pvalue; } ;
struct cpu_stack_walk {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  savedregs_size; int /*<<< orphan*/  params_size; int /*<<< orphan*/  locals_size; int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ PDB_FPO_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  hash_table_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pev_set_value (struct pevaluator*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vector_init (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void  pev_init(struct pevaluator* pev, struct cpu_stack_walk* csw,
                      PDB_FPO_DATA* fpoext, struct pdb_cmd_pair* cpair)
{
    pev->csw = csw;
    pool_init(&pev->pool, 512);
    vector_init(&pev->stack, sizeof(char*), 8);
    pev->stk_index = 0;
    hash_table_init(&pev->pool, &pev->values, 8);
    pev->error[0] = '\0';
    for (; cpair->name; cpair++)
        pev_set_value(pev, cpair->name, *cpair->pvalue);
    pev_set_value(pev, ".raSearchStart", fpoext->start);
    pev_set_value(pev, ".cbLocals",      fpoext->locals_size);
    pev_set_value(pev, ".cbParams",      fpoext->params_size);
    pev_set_value(pev, ".cbSavedRegs",   fpoext->savedregs_size);
}