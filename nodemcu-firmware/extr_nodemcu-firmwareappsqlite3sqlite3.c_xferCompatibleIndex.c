#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ pTable; int nKeyCol; scalar_t__ onError; scalar_t__* aiColumn; scalar_t__* aSortOrder; int /*<<< orphan*/  pPartIdxWhere; int /*<<< orphan*/ * azColl; TYPE_2__* aColExpr; } ;
struct TYPE_7__ {TYPE_1__* a; } ;
struct TYPE_6__ {int /*<<< orphan*/  pExpr; } ;
typedef  TYPE_3__ Index ;

/* Variables and functions */
 scalar_t__ XN_EXPR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3ExprCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_stricmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xferCompatibleIndex(Index *pDest, Index *pSrc){
  int i;
  assert( pDest && pSrc );
  assert( pDest->pTable!=pSrc->pTable );
  if( pDest->nKeyCol!=pSrc->nKeyCol ){
    return 0;   /* Different number of columns */
  }
  if( pDest->onError!=pSrc->onError ){
    return 0;   /* Different conflict resolution strategies */
  }
  for(i=0; i<pSrc->nKeyCol; i++){
    if( pSrc->aiColumn[i]!=pDest->aiColumn[i] ){
      return 0;   /* Different columns indexed */
    }
    if( pSrc->aiColumn[i]==XN_EXPR ){
      assert( pSrc->aColExpr!=0 && pDest->aColExpr!=0 );
      if( sqlite3ExprCompare(pSrc->aColExpr->a[i].pExpr,
                             pDest->aColExpr->a[i].pExpr, -1)!=0 ){
        return 0;   /* Different expressions in the index */
      }
    }
    if( pSrc->aSortOrder[i]!=pDest->aSortOrder[i] ){
      return 0;   /* Different sort orders */
    }
    if( sqlite3_stricmp(pSrc->azColl[i],pDest->azColl[i])!=0 ){
      return 0;   /* Different collating sequences */
    }
  }
  if( sqlite3ExprCompare(pSrc->pPartIdxWhere, pDest->pPartIdxWhere, -1) ){
    return 0;     /* Different WHERE clauses */
  }

  /* If no test above fails then the indices must be compatible */
  return 1;
}