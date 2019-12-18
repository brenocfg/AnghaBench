#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* pOwner; } ;
typedef  TYPE_3__ Window ;
struct TYPE_9__ {int nExpr; } ;
struct TYPE_6__ {TYPE_4__* pList; } ;
struct TYPE_7__ {TYPE_1__ x; } ;
typedef  TYPE_4__ ExprList ;

/* Variables and functions */

__attribute__((used)) static int windowArgCount(Window *pWin){
  ExprList *pList = pWin->pOwner->x.pList;
  return (pList ? pList->nExpr : 0);
}