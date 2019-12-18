#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WhereClause ;
struct TYPE_18__ {TYPE_5__* pIndex; } ;
typedef  TYPE_3__ Table ;
struct TYPE_22__ {scalar_t__ op; int iTable; scalar_t__ iColumn; } ;
struct TYPE_21__ {int nExpr; TYPE_2__* a; } ;
struct TYPE_20__ {int nKeyCol; struct TYPE_20__* pNext; } ;
struct TYPE_19__ {int nSrc; TYPE_1__* a; } ;
struct TYPE_17__ {int /*<<< orphan*/  pExpr; } ;
struct TYPE_16__ {int iCursor; TYPE_3__* pTab; } ;
typedef  TYPE_4__ SrcList ;
typedef  int /*<<< orphan*/  Parse ;
typedef  TYPE_5__ Index ;
typedef  TYPE_6__ ExprList ;
typedef  TYPE_7__ Expr ;
typedef  int /*<<< orphan*/  Bitmask ;

/* Variables and functions */
 int /*<<< orphan*/  IsUniqueIndex (TYPE_5__*) ; 
 scalar_t__ TK_COLUMN ; 
 int /*<<< orphan*/  WO_EQ ; 
 scalar_t__ findIndexCol (int /*<<< orphan*/ *,TYPE_6__*,int,TYPE_5__*,int) ; 
 scalar_t__ indexColumnNotNull (TYPE_5__*,int) ; 
 TYPE_7__* sqlite3ExprSkipCollate (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3WhereFindTerm (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 

__attribute__((used)) static int isDistinctRedundant(
  Parse *pParse,            /* Parsing context */
  SrcList *pTabList,        /* The FROM clause */
  WhereClause *pWC,         /* The WHERE clause */
  ExprList *pDistinct       /* The result set that needs to be DISTINCT */
){
  Table *pTab;
  Index *pIdx;
  int i;
  int iBase;

  /* If there is more than one table or sub-select in the FROM clause of
  ** this query, then it will not be possible to show that the DISTINCT
  ** clause is redundant. */
  if( pTabList->nSrc!=1 ) return 0;
  iBase = pTabList->a[0].iCursor;
  pTab = pTabList->a[0].pTab;

  /* If any of the expressions is an IPK column on table iBase, then return
  ** true. Note: The (p->iTable==iBase) part of this test may be false if the
  ** current SELECT is a correlated sub-query.
  */
  for(i=0; i<pDistinct->nExpr; i++){
    Expr *p = sqlite3ExprSkipCollate(pDistinct->a[i].pExpr);
    if( p->op==TK_COLUMN && p->iTable==iBase && p->iColumn<0 ) return 1;
  }

  /* Loop through all indices on the table, checking each to see if it makes
  ** the DISTINCT qualifier redundant. It does so if:
  **
  **   1. The index is itself UNIQUE, and
  **
  **   2. All of the columns in the index are either part of the pDistinct
  **      list, or else the WHERE clause contains a term of the form "col=X",
  **      where X is a constant value. The collation sequences of the
  **      comparison and select-list expressions must match those of the index.
  **
  **   3. All of those index columns for which the WHERE clause does not
  **      contain a "col=X" term are subject to a NOT NULL constraint.
  */
  for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
    if( !IsUniqueIndex(pIdx) ) continue;
    for(i=0; i<pIdx->nKeyCol; i++){
      if( 0==sqlite3WhereFindTerm(pWC, iBase, i, ~(Bitmask)0, WO_EQ, pIdx) ){
        if( findIndexCol(pParse, pDistinct, iBase, pIdx, i)<0 ) break;
        if( indexColumnNotNull(pIdx, i)==0 ) break;
      }
    }
    if( i==pIdx->nKeyCol ){
      /* This index implies that the DISTINCT qualifier is redundant. */
      return 1;
    }
  }

  return 0;
}