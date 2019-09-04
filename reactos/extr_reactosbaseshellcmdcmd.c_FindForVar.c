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
typedef  scalar_t__ UINT ;
struct TYPE_3__ {size_t firstvar; scalar_t__ varcount; int /*<<< orphan*/ ** values; struct TYPE_3__* prev; } ;
typedef  size_t TCHAR ;
typedef  int /*<<< orphan*/ * LPTSTR ;
typedef  TYPE_1__ FOR_CONTEXT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* fc ; 

__attribute__((used)) static LPTSTR FindForVar(TCHAR Var, BOOL *IsParam0)
{
    FOR_CONTEXT *Ctx;
    *IsParam0 = FALSE;
    for (Ctx = fc; Ctx != NULL; Ctx = Ctx->prev)
    {
        if ((UINT)(Var - Ctx->firstvar) < Ctx->varcount)
            return Ctx->values[Var - Ctx->firstvar];
    }
    return NULL;
}