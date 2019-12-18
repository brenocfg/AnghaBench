#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* pRename; } ;
struct TYPE_12__ {TYPE_6__* pParse; TYPE_2__ u; } ;
typedef  TYPE_3__ Walker ;
struct TYPE_15__ {scalar_t__ pTriggerTab; } ;
struct TYPE_10__ {scalar_t__ pTab; } ;
struct TYPE_14__ {scalar_t__ op; scalar_t__ iColumn; TYPE_1__ y; } ;
struct TYPE_13__ {scalar_t__ iCol; scalar_t__ pTab; } ;
typedef  TYPE_4__ RenameCtx ;
typedef  TYPE_5__ Expr ;

/* Variables and functions */
 scalar_t__ TK_COLUMN ; 
 scalar_t__ TK_TRIGGER ; 
 int WRC_Continue ; 
 int /*<<< orphan*/  renameTokenFind (TYPE_6__*,TYPE_4__*,void*) ; 

__attribute__((used)) static int renameColumnExprCb(Walker *pWalker, Expr *pExpr){
  RenameCtx *p = pWalker->u.pRename;
  if( pExpr->op==TK_TRIGGER 
   && pExpr->iColumn==p->iCol 
   && pWalker->pParse->pTriggerTab==p->pTab
  ){
    renameTokenFind(pWalker->pParse, p, (void*)pExpr);
  }else if( pExpr->op==TK_COLUMN 
   && pExpr->iColumn==p->iCol 
   && p->pTab==pExpr->y.pTab
  ){
    renameTokenFind(pWalker->pParse, p, (void*)pExpr);
  }
  return WRC_Continue;
}