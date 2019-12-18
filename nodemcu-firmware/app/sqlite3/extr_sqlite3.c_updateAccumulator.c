#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_18__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ExprList_item {int /*<<< orphan*/  pExpr; } ;
struct AggInfo_func {scalar_t__ iDistinct; TYPE_8__* pFunc; int /*<<< orphan*/  iMem; TYPE_18__* pExpr; } ;
struct AggInfo_col {int /*<<< orphan*/  iMem; int /*<<< orphan*/  pExpr; } ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_25__ {int funcFlags; } ;
struct TYPE_24__ {int directMode; int nFunc; int nAccumulator; struct AggInfo_col* aCol; struct AggInfo_func* aFunc; } ;
struct TYPE_23__ {int nExpr; struct ExprList_item* a; } ;
struct TYPE_22__ {int nMem; TYPE_2__* db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_21__ {int /*<<< orphan*/ * pDfltColl; } ;
struct TYPE_20__ {TYPE_4__* pList; } ;
struct TYPE_19__ {TYPE_1__ x; } ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ ExprList ;
typedef  int /*<<< orphan*/  CollSeq ;
typedef  TYPE_5__ AggInfo ;

/* Variables and functions */
 int /*<<< orphan*/  EP_xIsSelect ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_18__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_AggStep0 ; 
 int /*<<< orphan*/  OP_CollSeq ; 
 int /*<<< orphan*/  OP_If ; 
 int /*<<< orphan*/  P4_COLLSEQ ; 
 int /*<<< orphan*/  P4_FUNCDEF ; 
 int /*<<< orphan*/  SQLITE_ECEL_DUP ; 
 int SQLITE_FUNC_NEEDCOLL ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  codeDistinct (TYPE_3__*,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  sqlite3ExprCacheAffinityChange (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  sqlite3ExprCacheClear (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3ExprCode (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprCodeExprList (TYPE_3__*,TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3ExprCollSeq (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int sqlite3GetTempRange (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempRange (TYPE_3__*,int,int) ; 
 int sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAppendP4 (int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeMakeLabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void updateAccumulator(Parse *pParse, AggInfo *pAggInfo){
  Vdbe *v = pParse->pVdbe;
  int i;
  int regHit = 0;
  int addrHitTest = 0;
  struct AggInfo_func *pF;
  struct AggInfo_col *pC;

  pAggInfo->directMode = 1;
  for(i=0, pF=pAggInfo->aFunc; i<pAggInfo->nFunc; i++, pF++){
    int nArg;
    int addrNext = 0;
    int regAgg;
    ExprList *pList = pF->pExpr->x.pList;
    assert( !ExprHasProperty(pF->pExpr, EP_xIsSelect) );
    if( pList ){
      nArg = pList->nExpr;
      regAgg = sqlite3GetTempRange(pParse, nArg);
      sqlite3ExprCodeExprList(pParse, pList, regAgg, 0, SQLITE_ECEL_DUP);
    }else{
      nArg = 0;
      regAgg = 0;
    }
    if( pF->iDistinct>=0 ){
      addrNext = sqlite3VdbeMakeLabel(v);
      testcase( nArg==0 );  /* Error condition */
      testcase( nArg>1 );   /* Also an error */
      codeDistinct(pParse, pF->iDistinct, addrNext, 1, regAgg);
    }
    if( pF->pFunc->funcFlags & SQLITE_FUNC_NEEDCOLL ){
      CollSeq *pColl = 0;
      struct ExprList_item *pItem;
      int j;
      assert( pList!=0 );  /* pList!=0 if pF->pFunc has NEEDCOLL */
      for(j=0, pItem=pList->a; !pColl && j<nArg; j++, pItem++){
        pColl = sqlite3ExprCollSeq(pParse, pItem->pExpr);
      }
      if( !pColl ){
        pColl = pParse->db->pDfltColl;
      }
      if( regHit==0 && pAggInfo->nAccumulator ) regHit = ++pParse->nMem;
      sqlite3VdbeAddOp4(v, OP_CollSeq, regHit, 0, 0, (char *)pColl, P4_COLLSEQ);
    }
    sqlite3VdbeAddOp3(v, OP_AggStep0, 0, regAgg, pF->iMem);
    sqlite3VdbeAppendP4(v, pF->pFunc, P4_FUNCDEF);
    sqlite3VdbeChangeP5(v, (u8)nArg);
    sqlite3ExprCacheAffinityChange(pParse, regAgg, nArg);
    sqlite3ReleaseTempRange(pParse, regAgg, nArg);
    if( addrNext ){
      sqlite3VdbeResolveLabel(v, addrNext);
      sqlite3ExprCacheClear(pParse);
    }
  }

  /* Before populating the accumulator registers, clear the column cache.
  ** Otherwise, if any of the required column values are already present
  ** in registers, sqlite3ExprCode() may use OP_SCopy to copy the value
  ** to pC->iMem. But by the time the value is used, the original register
  ** may have been used, invalidating the underlying buffer holding the
  ** text or blob value. See ticket [883034dcb5].
  **
  ** Another solution would be to change the OP_SCopy used to copy cached
  ** values to an OP_Copy.
  */
  if( regHit ){
    addrHitTest = sqlite3VdbeAddOp1(v, OP_If, regHit); VdbeCoverage(v);
  }
  sqlite3ExprCacheClear(pParse);
  for(i=0, pC=pAggInfo->aCol; i<pAggInfo->nAccumulator; i++, pC++){
    sqlite3ExprCode(pParse, pC->pExpr, pC->iMem);
  }
  pAggInfo->directMode = 0;
  sqlite3ExprCacheClear(pParse);
  if( addrHitTest ){
    sqlite3VdbeJumpHere(v, addrHitTest);
  }
}