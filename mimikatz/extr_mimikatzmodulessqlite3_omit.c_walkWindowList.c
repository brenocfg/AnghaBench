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
struct TYPE_3__ {int /*<<< orphan*/  pFilter; int /*<<< orphan*/  pPartition; int /*<<< orphan*/  pOrderBy; struct TYPE_3__* pNextWin; } ;
typedef  TYPE_1__ Window ;
typedef  int /*<<< orphan*/  Walker ;

/* Variables and functions */
 int WRC_Abort ; 
 int WRC_Continue ; 
 scalar_t__ sqlite3WalkExpr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3WalkExprList (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int walkWindowList(Walker *pWalker, Window *pList){
  Window *pWin;
  for(pWin=pList; pWin; pWin=pWin->pNextWin){
    if( sqlite3WalkExprList(pWalker, pWin->pOrderBy) ) return WRC_Abort;
    if( sqlite3WalkExprList(pWalker, pWin->pPartition) ) return WRC_Abort;
    if( sqlite3WalkExpr(pWalker, pWin->pFilter) ) return WRC_Abort;
  }
  return WRC_Continue;
}