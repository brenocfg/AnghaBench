#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct WindowRewrite {int /*<<< orphan*/ * pSubSelect; } ;
struct TYPE_5__ {struct WindowRewrite* pRewrite; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
typedef  TYPE_2__ Walker ;
typedef  int /*<<< orphan*/  Select ;

/* Variables and functions */
 int WRC_Continue ; 
 int WRC_Prune ; 
 int /*<<< orphan*/  sqlite3WalkSelect (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int selectWindowRewriteSelectCb(Walker *pWalker, Select *pSelect){
  struct WindowRewrite *p = pWalker->u.pRewrite;
  Select *pSave = p->pSubSelect;
  if( pSave==pSelect ){
    return WRC_Continue;
  }else{
    p->pSubSelect = pSelect;
    sqlite3WalkSelect(pWalker, pSelect);
    p->pSubSelect = pSave;
  }
  return WRC_Prune;
}