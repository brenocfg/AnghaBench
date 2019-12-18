#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_16__ {int iECursor; int nExpr; } ;
struct TYPE_15__ {int nMem; int /*<<< orphan*/  nTab; } ;
struct TYPE_14__ {int selFlags; TYPE_4__* pOrderBy; } ;
struct TYPE_13__ {int eDest; int iSDParm; int iSdst; int /*<<< orphan*/  affSdst; } ;
typedef  TYPE_1__ SelectDest ;
typedef  TYPE_2__ Select ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  OPFLAG_APPEND ; 
 int /*<<< orphan*/  OPFLAG_CLEARCACHE ; 
 int /*<<< orphan*/  OP_Close ; 
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_IdxInsert ; 
 int /*<<< orphan*/  OP_Insert ; 
 int /*<<< orphan*/  OP_MakeRecord ; 
 int /*<<< orphan*/  OP_NewRowid ; 
 int /*<<< orphan*/  OP_Next ; 
 int /*<<< orphan*/  OP_OpenPseudo ; 
 int /*<<< orphan*/  OP_ResultRow ; 
 int /*<<< orphan*/  OP_Sort ; 
 int /*<<< orphan*/  OP_SorterData ; 
 int /*<<< orphan*/  OP_SorterNext ; 
 int /*<<< orphan*/  OP_SorterSort ; 
 int /*<<< orphan*/  OP_Yield ; 
 int SF_UseSorter ; 
 int SRT_Coroutine ; 
#define  SRT_EphemTab 131 
#define  SRT_Mem 130 
 int SRT_Output ; 
#define  SRT_Set 129 
#define  SRT_Table 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  codeOffset (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  sqlite3ExprCacheAffinityChange (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  sqlite3ExprCodeMove (TYPE_3__*,int,int,int) ; 
 int sqlite3GetTempReg (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeMakeLabel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void generateSortTail(
  Parse *pParse,    /* Parsing context */
  Select *p,        /* The SELECT statement */
  Vdbe *v,          /* Generate code into this VDBE */
  int nColumn,      /* Number of columns of data */
  SelectDest *pDest /* Write the sorted results here */
){
  int addrBreak = sqlite3VdbeMakeLabel(v);     /* Jump here to exit loop */
  int addrContinue = sqlite3VdbeMakeLabel(v);  /* Jump here for next cycle */
  int addr;
  int iTab;
  int pseudoTab = 0;
  ExprList *pOrderBy = p->pOrderBy;

  int eDest = pDest->eDest;
  int iParm = pDest->iSDParm;

  int regRow;
  int regRowid;

  iTab = pOrderBy->iECursor;
  regRow = sqlite3GetTempReg(pParse);
  if( eDest==SRT_Output || eDest==SRT_Coroutine ){
    pseudoTab = pParse->nTab++;
    sqlite3VdbeAddOp3(v, OP_OpenPseudo, pseudoTab, regRow, nColumn);
    regRowid = 0;
  }else{
    regRowid = sqlite3GetTempReg(pParse);
  }
  if( p->selFlags & SF_UseSorter ){
    int regSortOut = ++pParse->nMem;
    int ptab2 = pParse->nTab++;
    sqlite3VdbeAddOp3(v, OP_OpenPseudo, ptab2, regSortOut, pOrderBy->nExpr+2);
    addr = 1 + sqlite3VdbeAddOp2(v, OP_SorterSort, iTab, addrBreak);
    codeOffset(v, p, addrContinue);
    sqlite3VdbeAddOp2(v, OP_SorterData, iTab, regSortOut);
    sqlite3VdbeAddOp3(v, OP_Column, ptab2, pOrderBy->nExpr+1, regRow);
    sqlite3VdbeChangeP5(v, OPFLAG_CLEARCACHE);
  }else{
    addr = 1 + sqlite3VdbeAddOp2(v, OP_Sort, iTab, addrBreak);
    codeOffset(v, p, addrContinue);
    sqlite3VdbeAddOp3(v, OP_Column, iTab, pOrderBy->nExpr+1, regRow);
  }
  switch( eDest ){
    case SRT_Table:
    case SRT_EphemTab: {
      testcase( eDest==SRT_Table );
      testcase( eDest==SRT_EphemTab );
      sqlite3VdbeAddOp2(v, OP_NewRowid, iParm, regRowid);
      sqlite3VdbeAddOp3(v, OP_Insert, iParm, regRow, regRowid);
      sqlite3VdbeChangeP5(v, OPFLAG_APPEND);
      break;
    }
#ifndef SQLITE_OMIT_SUBQUERY
    case SRT_Set: {
      assert( nColumn==1 );
      sqlite3VdbeAddOp4(v, OP_MakeRecord, regRow, 1, regRowid,
                        &pDest->affSdst, 1);
      sqlite3ExprCacheAffinityChange(pParse, regRow, 1);
      sqlite3VdbeAddOp2(v, OP_IdxInsert, iParm, regRowid);
      break;
    }
    case SRT_Mem: {
      assert( nColumn==1 );
      sqlite3ExprCodeMove(pParse, regRow, iParm, 1);
      /* The LIMIT clause will terminate the loop for us */
      break;
    }
#endif
    default: {
      int i;
      assert( eDest==SRT_Output || eDest==SRT_Coroutine ); 
      testcase( eDest==SRT_Output );
      testcase( eDest==SRT_Coroutine );
      for(i=0; i<nColumn; i++){
        assert( regRow!=pDest->iSdst+i );
        sqlite3VdbeAddOp3(v, OP_Column, pseudoTab, i, pDest->iSdst+i);
        if( i==0 ){
          sqlite3VdbeChangeP5(v, OPFLAG_CLEARCACHE);
        }
      }
      if( eDest==SRT_Output ){
        sqlite3VdbeAddOp2(v, OP_ResultRow, pDest->iSdst, nColumn);
        sqlite3ExprCacheAffinityChange(pParse, pDest->iSdst, nColumn);
      }else{
        sqlite3VdbeAddOp1(v, OP_Yield, pDest->iSDParm);
      }
      break;
    }
  }
  sqlite3ReleaseTempReg(pParse, regRow);
  sqlite3ReleaseTempReg(pParse, regRowid);

  /* The bottom of the loop
  */
  sqlite3VdbeResolveLabel(v, addrContinue);
  if( p->selFlags & SF_UseSorter ){
    sqlite3VdbeAddOp2(v, OP_SorterNext, iTab, addr);
  }else{
    sqlite3VdbeAddOp2(v, OP_Next, iTab, addr);
  }
  sqlite3VdbeResolveLabel(v, addrBreak);
  if( eDest==SRT_Output || eDest==SRT_Coroutine ){
    sqlite3VdbeAddOp2(v, OP_Close, pseudoTab, 0);
  }
}