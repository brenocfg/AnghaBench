#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_9__ ;
typedef  struct TYPE_36__   TYPE_8__ ;
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_17__ ;
typedef  struct TYPE_27__   TYPE_14__ ;
typedef  struct TYPE_26__   TYPE_13__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_4__* pExpr; } ;
typedef  TYPE_11__ WhereTerm ;
struct TYPE_37__ {TYPE_8__* a; } ;
struct TYPE_36__ {TYPE_13__* pExpr; } ;
struct TYPE_35__ {TYPE_6__* pEList; } ;
struct TYPE_34__ {TYPE_5__* a; } ;
struct TYPE_33__ {TYPE_13__* pExpr; } ;
struct TYPE_32__ {TYPE_13__* pRight; TYPE_17__* pLeft; } ;
struct TYPE_31__ {TYPE_2__* pList; } ;
struct TYPE_30__ {TYPE_1__* a; } ;
struct TYPE_29__ {TYPE_13__* pExpr; } ;
struct TYPE_28__ {TYPE_3__ x; } ;
struct TYPE_27__ {int /*<<< orphan*/  zName; } ;
struct TYPE_23__ {TYPE_9__* pList; TYPE_7__* pSelect; } ;
struct TYPE_26__ {int flags; scalar_t__ op; int iTable; scalar_t__ iColumn; TYPE_10__ x; } ;
struct TYPE_25__ {scalar_t__* aiColumn; scalar_t__* aSortOrder; int /*<<< orphan*/ * azColl; int /*<<< orphan*/  pTable; scalar_t__ nColumn; } ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_12__ Index ;
typedef  TYPE_13__ Expr ;
typedef  TYPE_14__ CollSeq ;

/* Variables and functions */
 int EP_xIsSelect ; 
 int MIN (int,scalar_t__) ; 
 scalar_t__ TK_COLUMN ; 
 scalar_t__ XN_ROWID ; 
 TYPE_14__* sqlite3BinaryCompareCollSeq (int /*<<< orphan*/ *,TYPE_13__*,TYPE_13__*) ; 
 char sqlite3CompareAffinity (TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprAffinity (TYPE_13__*) ; 
 int sqlite3ExprVectorSize (TYPE_17__*) ; 
 scalar_t__ sqlite3StrICmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char sqlite3TableColumnAffinity (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int whereRangeVectorLen(
  Parse *pParse,       /* Parsing context */
  int iCur,            /* Cursor open on pIdx */
  Index *pIdx,         /* The index to be used for a inequality constraint */
  int nEq,             /* Number of prior equality constraints on same index */
  WhereTerm *pTerm     /* The vector inequality constraint */
){
  int nCmp = sqlite3ExprVectorSize(pTerm->pExpr->pLeft);
  int i;

  nCmp = MIN(nCmp, (pIdx->nColumn - nEq));
  for(i=1; i<nCmp; i++){
    /* Test if comparison i of pTerm is compatible with column (i+nEq)
    ** of the index. If not, exit the loop.  */
    char aff;                     /* Comparison affinity */
    char idxaff = 0;              /* Indexed columns affinity */
    CollSeq *pColl;               /* Comparison collation sequence */
    Expr *pLhs = pTerm->pExpr->pLeft->x.pList->a[i].pExpr;
    Expr *pRhs = pTerm->pExpr->pRight;
    if( pRhs->flags & EP_xIsSelect ){
      pRhs = pRhs->x.pSelect->pEList->a[i].pExpr;
    }else{
      pRhs = pRhs->x.pList->a[i].pExpr;
    }

    /* Check that the LHS of the comparison is a column reference to
    ** the right column of the right source table. And that the sort
    ** order of the index column is the same as the sort order of the
    ** leftmost index column.  */
    if( pLhs->op!=TK_COLUMN
     || pLhs->iTable!=iCur
     || pLhs->iColumn!=pIdx->aiColumn[i+nEq]
     || pIdx->aSortOrder[i+nEq]!=pIdx->aSortOrder[nEq]
    ){
      break;
    }

    testcase( pLhs->iColumn==XN_ROWID );
    aff = sqlite3CompareAffinity(pRhs, sqlite3ExprAffinity(pLhs));
    idxaff = sqlite3TableColumnAffinity(pIdx->pTable, pLhs->iColumn);
    if( aff!=idxaff ) break;

    pColl = sqlite3BinaryCompareCollSeq(pParse, pLhs, pRhs);
    if( pColl==0 ) break;
    if( sqlite3StrICmp(pColl->zName, pIdx->azColl[i+nEq]) ) break;
  }
  return i;
}