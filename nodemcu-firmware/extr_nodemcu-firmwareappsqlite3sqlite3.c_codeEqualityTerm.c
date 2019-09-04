#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_55__   TYPE_9__ ;
typedef  struct TYPE_54__   TYPE_8__ ;
typedef  struct TYPE_53__   TYPE_7__ ;
typedef  struct TYPE_52__   TYPE_6__ ;
typedef  struct TYPE_51__   TYPE_5__ ;
typedef  struct TYPE_50__   TYPE_4__ ;
typedef  struct TYPE_49__   TYPE_3__ ;
typedef  struct TYPE_48__   TYPE_2__ ;
typedef  struct TYPE_47__   TYPE_1__ ;
typedef  struct TYPE_46__   TYPE_17__ ;
typedef  struct TYPE_45__   TYPE_16__ ;
typedef  struct TYPE_44__   TYPE_15__ ;
typedef  struct TYPE_43__   TYPE_14__ ;
typedef  struct TYPE_42__   TYPE_13__ ;
typedef  struct TYPE_41__   TYPE_12__ ;
typedef  struct TYPE_40__   TYPE_11__ ;
typedef  struct TYPE_39__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct InLoop {int iCur; int /*<<< orphan*/  eEndLoopOp; int /*<<< orphan*/  addrInTop; } ;
struct TYPE_39__ {int /*<<< orphan*/  dbOptFlags; int /*<<< orphan*/  mallocFailed; } ;
typedef  TYPE_10__ sqlite3 ;
struct TYPE_40__ {int iField; TYPE_17__* pExpr; } ;
typedef  TYPE_11__ WhereTerm ;
struct TYPE_54__ {TYPE_7__* pIndex; } ;
struct TYPE_55__ {TYPE_8__ btree; } ;
struct TYPE_41__ {int wsFlags; int nLTerm; TYPE_11__** aLTerm; TYPE_9__ u; } ;
typedef  TYPE_12__ WhereLoop ;
struct TYPE_51__ {int nIn; struct InLoop* aInLoop; } ;
struct TYPE_52__ {TYPE_5__ in; } ;
struct TYPE_42__ {TYPE_6__ u; int /*<<< orphan*/  addrNxt; TYPE_12__* pWLoop; } ;
typedef  TYPE_13__ WhereLevel ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_53__ {scalar_t__* aSortOrder; } ;
struct TYPE_50__ {TYPE_16__* pList; TYPE_14__* pSelect; } ;
struct TYPE_47__ {scalar_t__ iOrderByCol; } ;
struct TYPE_48__ {TYPE_1__ x; } ;
struct TYPE_49__ {TYPE_17__* pExpr; TYPE_2__ u; } ;
struct TYPE_46__ {scalar_t__ op; int flags; int iTable; struct TYPE_46__* pLeft; TYPE_4__ x; int /*<<< orphan*/  pRight; } ;
struct TYPE_45__ {int nExpr; TYPE_3__* a; } ;
struct TYPE_44__ {TYPE_10__* db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_43__ {TYPE_16__* pEList; TYPE_16__* pOrderBy; } ;
typedef  TYPE_14__ Select ;
typedef  TYPE_15__ Parse ;
typedef  TYPE_16__ ExprList ;
typedef  TYPE_17__ Expr ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_11__*) ; 
 int EP_xIsSelect ; 
 int IN_INDEX_INDEX_DESC ; 
 int /*<<< orphan*/  IN_INDEX_LOOP ; 
 int IN_INDEX_NOOP ; 
 int IN_INDEX_ROWID ; 
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_IsNull ; 
 int /*<<< orphan*/  OP_Last ; 
 int /*<<< orphan*/  OP_NextIfOpen ; 
 int /*<<< orphan*/  OP_Noop ; 
 int /*<<< orphan*/  OP_Null ; 
 int /*<<< orphan*/  OP_PrevIfOpen ; 
 int /*<<< orphan*/  OP_Rewind ; 
 int /*<<< orphan*/  OP_Rowid ; 
 int /*<<< orphan*/  SQLITE_QueryFlattener ; 
 scalar_t__ TK_EQ ; 
 scalar_t__ TK_IN ; 
 scalar_t__ TK_IS ; 
 scalar_t__ TK_ISNULL ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageIf (int /*<<< orphan*/ *,int) ; 
 int WHERE_IN_ABLE ; 
 int WHERE_MULTI_OR ; 
 int WHERE_VIRTUALTABLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  disableTerm (TYPE_13__*,TYPE_11__*) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_10__*,int*) ; 
 scalar_t__ sqlite3DbMallocZero (TYPE_10__*,int) ; 
 struct InLoop* sqlite3DbReallocOrFree (TYPE_10__*,struct InLoop*,int) ; 
 int sqlite3ExprCodeTarget (TYPE_15__*,int /*<<< orphan*/ ,int) ; 
 TYPE_17__* sqlite3ExprDup (TYPE_10__*,TYPE_17__*,int /*<<< orphan*/ ) ; 
 TYPE_16__* sqlite3ExprListAppend (TYPE_15__*,TYPE_16__*,TYPE_17__*) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (TYPE_10__*,TYPE_16__*) ; 
 int sqlite3FindInIndex (TYPE_15__*,TYPE_17__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeMakeLabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int codeEqualityTerm(
  Parse *pParse,      /* The parsing context */
  WhereTerm *pTerm,   /* The term of the WHERE clause to be coded */
  WhereLevel *pLevel, /* The level of the FROM clause we are working on */
  int iEq,            /* Index of the equality term within this level */
  int bRev,           /* True for reverse-order IN operations */
  int iTarget         /* Attempt to leave results in this register */
){
  Expr *pX = pTerm->pExpr;
  Vdbe *v = pParse->pVdbe;
  int iReg;                  /* Register holding results */

  assert( pLevel->pWLoop->aLTerm[iEq]==pTerm );
  assert( iTarget>0 );
  if( pX->op==TK_EQ || pX->op==TK_IS ){
    iReg = sqlite3ExprCodeTarget(pParse, pX->pRight, iTarget);
  }else if( pX->op==TK_ISNULL ){
    iReg = iTarget;
    sqlite3VdbeAddOp2(v, OP_Null, 0, iReg);
#ifndef SQLITE_OMIT_SUBQUERY
  }else{
    int eType = IN_INDEX_NOOP;
    int iTab;
    struct InLoop *pIn;
    WhereLoop *pLoop = pLevel->pWLoop;
    int i;
    int nEq = 0;
    int *aiMap = 0;

    if( (pLoop->wsFlags & WHERE_VIRTUALTABLE)==0
      && pLoop->u.btree.pIndex!=0
      && pLoop->u.btree.pIndex->aSortOrder[iEq]
    ){
      testcase( iEq==0 );
      testcase( bRev );
      bRev = !bRev;
    }
    assert( pX->op==TK_IN );
    iReg = iTarget;

    for(i=0; i<iEq; i++){
      if( pLoop->aLTerm[i] && pLoop->aLTerm[i]->pExpr==pX ){
        disableTerm(pLevel, pTerm);
        return iTarget;
      }
    }
    for(i=iEq;i<pLoop->nLTerm; i++){
      if( ALWAYS(pLoop->aLTerm[i]) && pLoop->aLTerm[i]->pExpr==pX ) nEq++;
    }

    if( (pX->flags & EP_xIsSelect)==0 || pX->x.pSelect->pEList->nExpr==1 ){
      eType = sqlite3FindInIndex(pParse, pX, IN_INDEX_LOOP, 0, 0);
    }else{
      Select *pSelect = pX->x.pSelect;
      sqlite3 *db = pParse->db;
      u16 savedDbOptFlags = db->dbOptFlags;
      ExprList *pOrigRhs = pSelect->pEList;
      ExprList *pOrigLhs = pX->pLeft->x.pList;
      ExprList *pRhs = 0;         /* New Select.pEList for RHS */
      ExprList *pLhs = 0;         /* New pX->pLeft vector */

      for(i=iEq;i<pLoop->nLTerm; i++){
        if( pLoop->aLTerm[i]->pExpr==pX ){
          int iField = pLoop->aLTerm[i]->iField - 1;
          Expr *pNewRhs = sqlite3ExprDup(db, pOrigRhs->a[iField].pExpr, 0);
          Expr *pNewLhs = sqlite3ExprDup(db, pOrigLhs->a[iField].pExpr, 0);

          pRhs = sqlite3ExprListAppend(pParse, pRhs, pNewRhs);
          pLhs = sqlite3ExprListAppend(pParse, pLhs, pNewLhs);
        }
      }
      if( !db->mallocFailed ){
        Expr *pLeft = pX->pLeft;

        if( pSelect->pOrderBy ){
          /* If the SELECT statement has an ORDER BY clause, zero the
          ** iOrderByCol variables. These are set to non-zero when an
          ** ORDER BY term exactly matches one of the terms of the
          ** result-set. Since the result-set of the SELECT statement may
          ** have been modified or reordered, these variables are no longer
          ** set correctly.  Since setting them is just an optimization,
          ** it's easiest just to zero them here.  */
          ExprList *pOrderBy = pSelect->pOrderBy;
          for(i=0; i<pOrderBy->nExpr; i++){
            pOrderBy->a[i].u.x.iOrderByCol = 0;
          }
        }

        /* Take care here not to generate a TK_VECTOR containing only a
        ** single value. Since the parser never creates such a vector, some
        ** of the subroutines do not handle this case.  */
        if( pLhs->nExpr==1 ){
          pX->pLeft = pLhs->a[0].pExpr;
        }else{
          pLeft->x.pList = pLhs;
          aiMap = (int*)sqlite3DbMallocZero(pParse->db, sizeof(int) * nEq);
          testcase( aiMap==0 );
        }
        pSelect->pEList = pRhs;
        db->dbOptFlags |= SQLITE_QueryFlattener;
        eType = sqlite3FindInIndex(pParse, pX, IN_INDEX_LOOP, 0, aiMap);
        db->dbOptFlags = savedDbOptFlags;
        testcase( aiMap!=0 && aiMap[0]!=0 );
        pSelect->pEList = pOrigRhs;
        pLeft->x.pList = pOrigLhs;
        pX->pLeft = pLeft;
      }
      sqlite3ExprListDelete(pParse->db, pLhs);
      sqlite3ExprListDelete(pParse->db, pRhs);
    }

    if( eType==IN_INDEX_INDEX_DESC ){
      testcase( bRev );
      bRev = !bRev;
    }
    iTab = pX->iTable;
    sqlite3VdbeAddOp2(v, bRev ? OP_Last : OP_Rewind, iTab, 0);
    VdbeCoverageIf(v, bRev);
    VdbeCoverageIf(v, !bRev);
    assert( (pLoop->wsFlags & WHERE_MULTI_OR)==0 );

    pLoop->wsFlags |= WHERE_IN_ABLE;
    if( pLevel->u.in.nIn==0 ){
      pLevel->addrNxt = sqlite3VdbeMakeLabel(v);
    }

    i = pLevel->u.in.nIn;
    pLevel->u.in.nIn += nEq;
    pLevel->u.in.aInLoop =
       sqlite3DbReallocOrFree(pParse->db, pLevel->u.in.aInLoop,
                              sizeof(pLevel->u.in.aInLoop[0])*pLevel->u.in.nIn);
    pIn = pLevel->u.in.aInLoop;
    if( pIn ){
      int iMap = 0;               /* Index in aiMap[] */
      pIn += i;
      for(i=iEq;i<pLoop->nLTerm; i++){
        if( pLoop->aLTerm[i]->pExpr==pX ){
          int iOut = iReg + i - iEq;
          if( eType==IN_INDEX_ROWID ){
            testcase( nEq>1 );  /* Happens with a UNIQUE index on ROWID */
            pIn->addrInTop = sqlite3VdbeAddOp2(v, OP_Rowid, iTab, iOut);
          }else{
            int iCol = aiMap ? aiMap[iMap++] : 0;
            pIn->addrInTop = sqlite3VdbeAddOp3(v,OP_Column,iTab, iCol, iOut);
          }
          sqlite3VdbeAddOp1(v, OP_IsNull, iOut); VdbeCoverage(v);
          if( i==iEq ){
            pIn->iCur = iTab;
            pIn->eEndLoopOp = bRev ? OP_PrevIfOpen : OP_NextIfOpen;
          }else{
            pIn->eEndLoopOp = OP_Noop;
          }
          pIn++;
        }
      }
    }else{
      pLevel->u.in.nIn = 0;
    }
    sqlite3DbFree(pParse->db, aiMap);
#endif
  }
  disableTerm(pLevel, pTerm);
  return iReg;
}