#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct Op2   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct Op2 {char const* zOp; unsigned char eOp2; } ;
struct TYPE_10__ {int /*<<< orphan*/  zToken; } ;
struct TYPE_8__ {TYPE_4__* pList; } ;
struct TYPE_12__ {scalar_t__ op; TYPE_3__ u; int /*<<< orphan*/  pTab; TYPE_1__ x; } ;
struct TYPE_11__ {int nExpr; TYPE_2__* a; } ;
struct TYPE_9__ {TYPE_5__* pExpr; } ;
typedef  TYPE_4__ ExprList ;
typedef  TYPE_5__ Expr ;

/* Variables and functions */
 int ArraySize (TYPE_7__ const*) ; 
 int /*<<< orphan*/  IsVirtual (int /*<<< orphan*/ ) ; 
#define  SQLITE_INDEX_CONSTRAINT_GLOB 131 
#define  SQLITE_INDEX_CONSTRAINT_LIKE 130 
#define  SQLITE_INDEX_CONSTRAINT_MATCH 129 
#define  SQLITE_INDEX_CONSTRAINT_REGEXP 128 
 scalar_t__ TK_COLUMN ; 
 scalar_t__ TK_FUNCTION ; 
 scalar_t__ sqlite3StrICmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int isMatchOfColumn(
  Expr *pExpr,                    /* Test this expression */
  unsigned char *peOp2            /* OUT: 0 for MATCH, or else an op2 value */
){
  static const struct Op2 {
    const char *zOp;
    unsigned char eOp2;
  } aOp[] = {
    { "match",  SQLITE_INDEX_CONSTRAINT_MATCH },
    { "glob",   SQLITE_INDEX_CONSTRAINT_GLOB },
    { "like",   SQLITE_INDEX_CONSTRAINT_LIKE },
    { "regexp", SQLITE_INDEX_CONSTRAINT_REGEXP }
  };
  ExprList *pList;
  Expr *pCol;                     /* Column reference */
  int i;

  if( pExpr->op!=TK_FUNCTION ){
    return 0;
  }
  pList = pExpr->x.pList;
  if( pList==0 || pList->nExpr!=2 ){
    return 0;
  }
  pCol = pList->a[1].pExpr;
  if( pCol->op!=TK_COLUMN || !IsVirtual(pCol->pTab) ){
    return 0;
  }
  for(i=0; i<ArraySize(aOp); i++){
    if( sqlite3StrICmp(pExpr->u.zToken, aOp[i].zOp)==0 ){
      *peOp2 = aOp[i].eOp2;
      return 1;
    }
  }
  return 0;
}