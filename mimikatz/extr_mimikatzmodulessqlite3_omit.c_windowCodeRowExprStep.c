#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {scalar_t__ eStart; scalar_t__ eEnd; int iEphCsr; scalar_t__ pStart; scalar_t__ pEnd; } ;
typedef  TYPE_1__ Window ;
typedef  int /*<<< orphan*/  WhereInfo ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_22__ {int nMem; int /*<<< orphan*/  nTab; } ;
struct TYPE_21__ {TYPE_1__* pWin; } ;
typedef  TYPE_2__ Select ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Copy ; 
 int /*<<< orphan*/  OP_Ge ; 
 int /*<<< orphan*/  OP_Goto ; 
 int /*<<< orphan*/  OP_IfPos ; 
 int /*<<< orphan*/  OP_Le ; 
 int /*<<< orphan*/  OP_Next ; 
 int /*<<< orphan*/  OP_Once ; 
 int /*<<< orphan*/  OP_OpenDup ; 
 int /*<<< orphan*/  OP_ResetSorter ; 
 int /*<<< orphan*/  OP_Return ; 
 int /*<<< orphan*/  OP_Rewind ; 
 int /*<<< orphan*/  OP_Subtract ; 
 scalar_t__ TK_CURRENT ; 
 scalar_t__ TK_FOLLOWING ; 
 scalar_t__ TK_PRECEDING ; 
 scalar_t__ TK_UNBOUNDED ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageAlwaysTaken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageNeverNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageNeverTaken (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ExprCode (TYPE_3__*,scalar_t__,int) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_3__*) ; 
 int sqlite3VdbeAddOp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeMakeLabel (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  windowAggFinal (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windowAggStep (TYPE_3__*,TYPE_1__*,int,int,int,int) ; 
 int /*<<< orphan*/  windowCheckIntValue (TYPE_3__*,int,int) ; 
 int windowInitAccum (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  windowPartitionCache (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/  windowReturnOneRow (TYPE_3__*,TYPE_1__*,int,int) ; 

__attribute__((used)) static void windowCodeRowExprStep(
  Parse *pParse, 
  Select *p,
  WhereInfo *pWInfo,
  int regGosub, 
  int addrGosub
){
  Window *pMWin = p->pWin;
  Vdbe *v = sqlite3GetVdbe(pParse);
  int regFlushPart;               /* Register for "Gosub flush_partition" */
  int lblFlushPart;               /* Label for "Gosub flush_partition" */
  int lblFlushDone;               /* Label for "Gosub flush_partition_done" */

  int regArg;
  int addr;
  int csrStart = pParse->nTab++;
  int csrEnd = pParse->nTab++;
  int regStart;                    /* Value of <expr> PRECEDING */
  int regEnd;                      /* Value of <expr> FOLLOWING */
  int addrGoto;
  int addrTop;
  int addrIfPos1 = 0;
  int addrIfPos2 = 0;
  int regSize = 0;

  assert( pMWin->eStart==TK_PRECEDING 
       || pMWin->eStart==TK_CURRENT 
       || pMWin->eStart==TK_FOLLOWING 
       || pMWin->eStart==TK_UNBOUNDED 
  );
  assert( pMWin->eEnd==TK_FOLLOWING 
       || pMWin->eEnd==TK_CURRENT 
       || pMWin->eEnd==TK_UNBOUNDED 
       || pMWin->eEnd==TK_PRECEDING 
  );

  /* Allocate register and label for the "flush_partition" sub-routine. */
  regFlushPart = ++pParse->nMem;
  lblFlushPart = sqlite3VdbeMakeLabel(pParse);
  lblFlushDone = sqlite3VdbeMakeLabel(pParse);

  regStart = ++pParse->nMem;
  regEnd = ++pParse->nMem;

  windowPartitionCache(pParse, p, pWInfo, regFlushPart, lblFlushPart, &regSize);

  addrGoto = sqlite3VdbeAddOp0(v, OP_Goto);

  /* Start of "flush_partition" */
  sqlite3VdbeResolveLabel(v, lblFlushPart);
  sqlite3VdbeAddOp2(v, OP_Once, 0, sqlite3VdbeCurrentAddr(v)+3);
  VdbeCoverage(v);
  VdbeComment((v, "Flush_partition subroutine"));
  sqlite3VdbeAddOp2(v, OP_OpenDup, csrStart, pMWin->iEphCsr);
  sqlite3VdbeAddOp2(v, OP_OpenDup, csrEnd, pMWin->iEphCsr);

  /* If either regStart or regEnd are not non-negative integers, throw 
  ** an exception.  */
  if( pMWin->pStart ){
    sqlite3ExprCode(pParse, pMWin->pStart, regStart);
    windowCheckIntValue(pParse, regStart, 0);
  }
  if( pMWin->pEnd ){
    sqlite3ExprCode(pParse, pMWin->pEnd, regEnd);
    windowCheckIntValue(pParse, regEnd, 1);
  }

  /* If this is "ROWS <expr1> FOLLOWING AND ROWS <expr2> FOLLOWING", do:
  **
  **   if( regEnd<regStart ){
  **     // The frame always consists of 0 rows
  **     regStart = regSize;
  **   }
  **   regEnd = regEnd - regStart;
  */
  if( pMWin->pEnd && pMWin->eStart==TK_FOLLOWING ){
    assert( pMWin->pStart!=0 );
    assert( pMWin->eEnd==TK_FOLLOWING );
    sqlite3VdbeAddOp3(v, OP_Ge, regStart, sqlite3VdbeCurrentAddr(v)+2, regEnd);
    VdbeCoverageNeverNull(v);
    sqlite3VdbeAddOp2(v, OP_Copy, regSize, regStart);
    sqlite3VdbeAddOp3(v, OP_Subtract, regStart, regEnd, regEnd);
  }

  if( pMWin->pStart && pMWin->eEnd==TK_PRECEDING ){
    assert( pMWin->pEnd!=0 );
    assert( pMWin->eStart==TK_PRECEDING );
    sqlite3VdbeAddOp3(v, OP_Le, regStart, sqlite3VdbeCurrentAddr(v)+3, regEnd);
    VdbeCoverageNeverNull(v);
    sqlite3VdbeAddOp2(v, OP_Copy, regSize, regStart);
    sqlite3VdbeAddOp2(v, OP_Copy, regSize, regEnd);
  }

  /* Initialize the accumulator register for each window function to NULL */
  regArg = windowInitAccum(pParse, pMWin);

  sqlite3VdbeAddOp2(v, OP_Rewind, pMWin->iEphCsr, lblFlushDone);
  VdbeCoverage(v);
  sqlite3VdbeAddOp2(v, OP_Rewind, csrStart, lblFlushDone);
  VdbeCoverageNeverTaken(v);
  sqlite3VdbeChangeP5(v, 1);
  sqlite3VdbeAddOp2(v, OP_Rewind, csrEnd, lblFlushDone);
  VdbeCoverageNeverTaken(v);
  sqlite3VdbeChangeP5(v, 1);

  /* Invoke AggStep function for each window function using the row that
  ** csrEnd currently points to. Or, if csrEnd is already at EOF,
  ** do nothing.  */
  addrTop = sqlite3VdbeCurrentAddr(v);
  if( pMWin->eEnd==TK_PRECEDING ){
    addrIfPos1 = sqlite3VdbeAddOp3(v, OP_IfPos, regEnd, 0 , 1);
    VdbeCoverage(v);
  }
  sqlite3VdbeAddOp2(v, OP_Next, csrEnd, sqlite3VdbeCurrentAddr(v)+2);
  VdbeCoverage(v);
  addr = sqlite3VdbeAddOp0(v, OP_Goto);
  windowAggStep(pParse, pMWin, csrEnd, 0, regArg, regSize);
  if( pMWin->eEnd==TK_UNBOUNDED ){
    sqlite3VdbeAddOp2(v, OP_Goto, 0, addrTop);
    sqlite3VdbeJumpHere(v, addr);
    addrTop = sqlite3VdbeCurrentAddr(v);
  }else{
    sqlite3VdbeJumpHere(v, addr);
    if( pMWin->eEnd==TK_PRECEDING ){
      sqlite3VdbeJumpHere(v, addrIfPos1);
    }
  }

  if( pMWin->eEnd==TK_FOLLOWING ){
    addrIfPos1 = sqlite3VdbeAddOp3(v, OP_IfPos, regEnd, 0 , 1);
    VdbeCoverage(v);
  }
  if( pMWin->eStart==TK_FOLLOWING ){
    addrIfPos2 = sqlite3VdbeAddOp3(v, OP_IfPos, regStart, 0 , 1);
    VdbeCoverage(v);
  }
  windowAggFinal(pParse, pMWin, 0);
  windowReturnOneRow(pParse, pMWin, regGosub, addrGosub);
  sqlite3VdbeAddOp2(v, OP_Next, pMWin->iEphCsr, sqlite3VdbeCurrentAddr(v)+2);
  VdbeCoverage(v);
  sqlite3VdbeAddOp2(v, OP_Goto, 0, lblFlushDone);
  if( pMWin->eStart==TK_FOLLOWING ){
    sqlite3VdbeJumpHere(v, addrIfPos2);
  }

  if( pMWin->eStart==TK_CURRENT 
   || pMWin->eStart==TK_PRECEDING 
   || pMWin->eStart==TK_FOLLOWING 
  ){
    int lblSkipInverse = sqlite3VdbeMakeLabel(pParse);;
    if( pMWin->eStart==TK_PRECEDING ){
      sqlite3VdbeAddOp3(v, OP_IfPos, regStart, lblSkipInverse, 1);
      VdbeCoverage(v);
    }
    if( pMWin->eStart==TK_FOLLOWING ){
      sqlite3VdbeAddOp2(v, OP_Next, csrStart, sqlite3VdbeCurrentAddr(v)+2);
      VdbeCoverage(v);
      sqlite3VdbeAddOp2(v, OP_Goto, 0, lblSkipInverse);
    }else{
      sqlite3VdbeAddOp2(v, OP_Next, csrStart, sqlite3VdbeCurrentAddr(v)+1);
      VdbeCoverageAlwaysTaken(v);
    }
    windowAggStep(pParse, pMWin, csrStart, 1, regArg, regSize);
    sqlite3VdbeResolveLabel(v, lblSkipInverse);
  }
  if( pMWin->eEnd==TK_FOLLOWING ){
    sqlite3VdbeJumpHere(v, addrIfPos1);
  }
  sqlite3VdbeAddOp2(v, OP_Goto, 0, addrTop);

  /* flush_partition_done: */
  sqlite3VdbeResolveLabel(v, lblFlushDone);
  sqlite3VdbeAddOp1(v, OP_ResetSorter, pMWin->iEphCsr);
  sqlite3VdbeAddOp1(v, OP_Return, regFlushPart);
  VdbeComment((v, "end flush_partition subroutine"));

  /* Jump to here to skip over flush_partition */
  sqlite3VdbeJumpHere(v, addrGoto);
}