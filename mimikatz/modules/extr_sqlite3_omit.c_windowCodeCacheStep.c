#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ eStart; scalar_t__ eEnd; int iEphCsr; scalar_t__ eType; int nBufferCol; int regPart; TYPE_4__* pOrderBy; TYPE_4__* pPartition; } ;
typedef  TYPE_1__ Window ;
typedef  int /*<<< orphan*/  WhereInfo ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_22__ {int nExpr; } ;
struct TYPE_21__ {int nMem; int /*<<< orphan*/  nTab; } ;
struct TYPE_20__ {TYPE_1__* pWin; } ;
typedef  TYPE_2__ Select ;
typedef  TYPE_3__ Parse ;
typedef  int /*<<< orphan*/  KeyInfo ;
typedef  TYPE_4__ ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  OP_AddImm ; 
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_Compare ; 
 int /*<<< orphan*/  OP_Copy ; 
 int /*<<< orphan*/  OP_Goto ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  OP_Jump ; 
 int /*<<< orphan*/  OP_Next ; 
 int /*<<< orphan*/  OP_Once ; 
 int /*<<< orphan*/  OP_OpenDup ; 
 int /*<<< orphan*/  OP_ResetSorter ; 
 int /*<<< orphan*/  OP_Return ; 
 int /*<<< orphan*/  OP_Rewind ; 
 int /*<<< orphan*/  P4_KEYINFO ; 
 scalar_t__ TK_CURRENT ; 
 scalar_t__ TK_RANGE ; 
 scalar_t__ TK_UNBOUNDED ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageNeverTaken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_3__*) ; 
 int /*<<< orphan*/ * sqlite3KeyInfoFromExprList (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeAddOp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAppendP4 (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeMakeLabel (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  windowAggStep (TYPE_3__*,TYPE_1__*,int,int /*<<< orphan*/ ,int,int) ; 
 int windowInitAccum (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  windowPartitionCache (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  windowReturnRows (TYPE_3__*,TYPE_1__*,int,int,int,int,int) ; 

__attribute__((used)) static void windowCodeCacheStep(
  Parse *pParse, 
  Select *p,
  WhereInfo *pWInfo,
  int regGosub, 
  int addrGosub
){
  Window *pMWin = p->pWin;
  Vdbe *v = sqlite3GetVdbe(pParse);
  int k;
  int addr;
  ExprList *pPart = pMWin->pPartition;
  ExprList *pOrderBy = pMWin->pOrderBy;
  int nPeer = pOrderBy ? pOrderBy->nExpr : 0;
  int regNewPeer;

  int addrGoto;                   /* Address of Goto used to jump flush_par.. */
  int addrNext;                   /* Jump here for next iteration of loop */
  int regFlushPart;
  int lblFlushPart;
  int csrLead;
  int regCtr;
  int regArg;                     /* Register array to martial function args */
  int regSize;
  int lblEmpty;
  int bReverse = pMWin->pOrderBy && pMWin->eStart==TK_CURRENT 
          && pMWin->eEnd==TK_UNBOUNDED;

  assert( (pMWin->eStart==TK_UNBOUNDED && pMWin->eEnd==TK_CURRENT) 
       || (pMWin->eStart==TK_UNBOUNDED && pMWin->eEnd==TK_UNBOUNDED) 
       || (pMWin->eStart==TK_CURRENT && pMWin->eEnd==TK_CURRENT) 
       || (pMWin->eStart==TK_CURRENT && pMWin->eEnd==TK_UNBOUNDED) 
  );

  lblEmpty = sqlite3VdbeMakeLabel(pParse);
  regNewPeer = pParse->nMem+1;
  pParse->nMem += nPeer;

  /* Allocate register and label for the "flush_partition" sub-routine. */
  regFlushPart = ++pParse->nMem;
  lblFlushPart = sqlite3VdbeMakeLabel(pParse);

  csrLead = pParse->nTab++;
  regCtr = ++pParse->nMem;

  windowPartitionCache(pParse, p, pWInfo, regFlushPart, lblFlushPart, &regSize);
  addrGoto = sqlite3VdbeAddOp0(v, OP_Goto);

  /* Start of "flush_partition" */
  sqlite3VdbeResolveLabel(v, lblFlushPart);
  sqlite3VdbeAddOp2(v, OP_Once, 0, sqlite3VdbeCurrentAddr(v)+2);
  VdbeCoverage(v);
  sqlite3VdbeAddOp2(v, OP_OpenDup, csrLead, pMWin->iEphCsr);

  /* Initialize the accumulator register for each window function to NULL */
  regArg = windowInitAccum(pParse, pMWin);

  sqlite3VdbeAddOp2(v, OP_Integer, 0, regCtr);
  sqlite3VdbeAddOp2(v, OP_Rewind, csrLead, lblEmpty);
  VdbeCoverage(v);
  sqlite3VdbeAddOp2(v, OP_Rewind, pMWin->iEphCsr, lblEmpty);
  VdbeCoverageNeverTaken(v);

  if( bReverse ){
    int addr2 = sqlite3VdbeCurrentAddr(v);
    windowAggStep(pParse, pMWin, csrLead, 0, regArg, regSize);
    sqlite3VdbeAddOp2(v, OP_Next, csrLead, addr2);
    VdbeCoverage(v);
    sqlite3VdbeAddOp2(v, OP_Rewind, csrLead, lblEmpty);
    VdbeCoverageNeverTaken(v);
  }
  addrNext = sqlite3VdbeCurrentAddr(v);

  if( pOrderBy && (pMWin->eEnd==TK_CURRENT || pMWin->eStart==TK_CURRENT) ){
    int bCurrent = (pMWin->eStart==TK_CURRENT);
    int addrJump = 0;             /* Address of OP_Jump below */
    if( pMWin->eType==TK_RANGE ){
      int iOff = pMWin->nBufferCol + (pPart ? pPart->nExpr : 0);
      int regPeer = pMWin->regPart + (pPart ? pPart->nExpr : 0);
      KeyInfo *pKeyInfo = sqlite3KeyInfoFromExprList(pParse, pOrderBy, 0, 0);
      for(k=0; k<nPeer; k++){
        sqlite3VdbeAddOp3(v, OP_Column, csrLead, iOff+k, regNewPeer+k);
      }
      addr = sqlite3VdbeAddOp3(v, OP_Compare, regNewPeer, regPeer, nPeer);
      sqlite3VdbeAppendP4(v, (void*)pKeyInfo, P4_KEYINFO);
      addrJump = sqlite3VdbeAddOp3(v, OP_Jump, addr+2, 0, addr+2);
      VdbeCoverage(v);
      sqlite3VdbeAddOp3(v, OP_Copy, regNewPeer, regPeer, nPeer-1);
    }

    windowReturnRows(pParse, pMWin, regCtr, regGosub, addrGosub, 
        (bCurrent ? regArg : 0), (bCurrent ? regSize : 0)
    );
    if( addrJump ) sqlite3VdbeJumpHere(v, addrJump);
  }

  if( bReverse==0 ){
    windowAggStep(pParse, pMWin, csrLead, 0, regArg, regSize);
  }
  sqlite3VdbeAddOp2(v, OP_AddImm, regCtr, 1);
  sqlite3VdbeAddOp2(v, OP_Next, csrLead, addrNext);
  VdbeCoverage(v);

  windowReturnRows(pParse, pMWin, regCtr, regGosub, addrGosub, 0, 0);

  sqlite3VdbeResolveLabel(v, lblEmpty);
  sqlite3VdbeAddOp1(v, OP_ResetSorter, pMWin->iEphCsr);
  sqlite3VdbeAddOp1(v, OP_Return, regFlushPart);

  /* Jump to here to skip over flush_partition */
  sqlite3VdbeJumpHere(v, addrGoto);
}