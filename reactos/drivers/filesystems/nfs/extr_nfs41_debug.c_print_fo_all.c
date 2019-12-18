#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pVNetRoot; } ;
struct TYPE_6__ {int /*<<< orphan*/  pNetRoot; int /*<<< orphan*/  OpenCount; } ;
struct TYPE_5__ {TYPE_3__* pFcb; TYPE_4__* pRelevantSrvOpen; int /*<<< orphan*/  pFobx; } ;
typedef  TYPE_1__* PRX_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  DbgP (char*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void print_fo_all(int on, PRX_CONTEXT c)
{
    if (!on) return;
    if (c->pFcb && c->pRelevantSrvOpen)
        DbgP("OpenCount %d FCB %p SRV %p FOBX %p VNET %p NET %p\n", 
            c->pFcb->OpenCount, c->pFcb, c->pRelevantSrvOpen, c->pFobx,
            c->pRelevantSrvOpen->pVNetRoot, c->pFcb->pNetRoot);
}