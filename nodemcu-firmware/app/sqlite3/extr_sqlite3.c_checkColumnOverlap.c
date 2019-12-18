#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_4__ {int /*<<< orphan*/  zName; } ;
typedef  int /*<<< orphan*/  IdList ;
typedef  TYPE_2__ ExprList ;

/* Variables and functions */
 scalar_t__ NEVER (int) ; 
 scalar_t__ sqlite3IdListIndex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkColumnOverlap(IdList *pIdList, ExprList *pEList){
  int e;
  if( pIdList==0 || NEVER(pEList==0) ) return 1;
  for(e=0; e<pEList->nExpr; e++){
    if( sqlite3IdListIndex(pIdList, pEList->a[e].zName)>=0 ) return 1;
  }
  return 0;
}