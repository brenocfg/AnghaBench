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
struct pevaluator {int /*<<< orphan*/  pool; } ;
struct pdb_cmd_pair {int /*<<< orphan*/ * pvalue; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ pev_get_val (struct pevaluator*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL  pev_free(struct pevaluator* pev, struct pdb_cmd_pair* cpair)
{
    DWORD_PTR   val;

    if (cpair) for (; cpair->name; cpair++)
    {
        if (pev_get_val(pev, cpair->name, &val))
            *cpair->pvalue = val;
    }
    pool_destroy(&pev->pool);
    return TRUE;
}