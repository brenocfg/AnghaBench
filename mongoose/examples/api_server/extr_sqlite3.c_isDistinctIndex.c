#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_5__* pExpr; } ;
typedef  TYPE_2__ WhereTerm ;
typedef  int /*<<< orphan*/  WhereClause ;
struct TYPE_17__ {scalar_t__ op; int iTable; int /*<<< orphan*/  pRight; int /*<<< orphan*/  pLeft; int /*<<< orphan*/  iColumn; } ;
struct TYPE_16__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_15__ {scalar_t__ zName; int nColumn; } ;
struct TYPE_13__ {int /*<<< orphan*/  pExpr; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_3__ Index ;
typedef  TYPE_4__ ExprList ;
typedef  TYPE_5__ Expr ;
typedef  int /*<<< orphan*/  CollSeq ;
typedef  int Bitmask ;

/* Variables and functions */
 int BMS ; 
 scalar_t__ TK_COLUMN ; 
 int /*<<< orphan*/  WO_EQ ; 
 int /*<<< orphan*/  assert (int) ; 
 int findIndexCol (int /*<<< orphan*/ *,TYPE_4__*,int,TYPE_3__*,int) ; 
 TYPE_2__* findTerm (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3BinaryCompareCollSeq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3ExprCollSeq (int /*<<< orphan*/ *,TYPE_5__*) ; 
 TYPE_5__* sqlite3ExprSkipCollate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int isDistinctIndex(
  Parse *pParse,                  /* Parsing context */
  WhereClause *pWC,               /* The WHERE clause */
  Index *pIdx,                    /* The index being considered */
  int base,                       /* Cursor number for the table pIdx is on */
  ExprList *pDistinct,            /* The DISTINCT expressions */
  int nEqCol                      /* Number of index columns with == */
){
  Bitmask mask = 0;               /* Mask of unaccounted for pDistinct exprs */
  int i;                          /* Iterator variable */

  assert( pDistinct!=0 );
  if( pIdx->zName==0 || pDistinct->nExpr>=BMS ) return 0;
  testcase( pDistinct->nExpr==BMS-1 );

  /* Loop through all the expressions in the distinct list. If any of them
  ** are not simple column references, return early. Otherwise, test if the
  ** WHERE clause contains a "col=X" clause. If it does, the expression
  ** can be ignored. If it does not, and the column does not belong to the
  ** same table as index pIdx, return early. Finally, if there is no
  ** matching "col=X" expression and the column is on the same table as pIdx,
  ** set the corresponding bit in variable mask.
  */
  for(i=0; i<pDistinct->nExpr; i++){
    WhereTerm *pTerm;
    Expr *p = sqlite3ExprSkipCollate(pDistinct->a[i].pExpr);
    if( p->op!=TK_COLUMN ) return 0;
    pTerm = findTerm(pWC, p->iTable, p->iColumn, ~(Bitmask)0, WO_EQ, 0);
    if( pTerm ){
      Expr *pX = pTerm->pExpr;
      CollSeq *p1 = sqlite3BinaryCompareCollSeq(pParse, pX->pLeft, pX->pRight);
      CollSeq *p2 = sqlite3ExprCollSeq(pParse, p);
      if( p1==p2 ) continue;
    }
    if( p->iTable!=base ) return 0;
    mask |= (((Bitmask)1) << i);
  }

  for(i=nEqCol; mask && i<pIdx->nColumn; i++){
    int iExpr = findIndexCol(pParse, pDistinct, base, pIdx, i);
    if( iExpr<0 ) break;
    mask &= ~(((Bitmask)1) << iExpr);
  }

  return (mask==0);
}