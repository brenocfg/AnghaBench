#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int nBufferCol; int regPart; int iEphCsr; TYPE_7__* pPartition; } ;
typedef  TYPE_4__ Window ;
typedef  int /*<<< orphan*/  WhereInfo ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_19__ {int nExpr; } ;
struct TYPE_18__ {int nMem; } ;
struct TYPE_17__ {TYPE_3__* pSrc; TYPE_4__* pWin; } ;
struct TYPE_15__ {TYPE_2__* a; } ;
struct TYPE_14__ {int iCursor; TYPE_1__* pTab; } ;
struct TYPE_13__ {int nCol; } ;
typedef  TYPE_5__ Select ;
typedef  TYPE_6__ Parse ;
typedef  int /*<<< orphan*/  KeyInfo ;
typedef  TYPE_7__ ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_Compare ; 
 int /*<<< orphan*/  OP_Copy ; 
 int /*<<< orphan*/  OP_Gosub ; 
 int /*<<< orphan*/  OP_Insert ; 
 int /*<<< orphan*/  OP_Jump ; 
 int /*<<< orphan*/  OP_MakeRecord ; 
 int /*<<< orphan*/  OP_NewRowid ; 
 int /*<<< orphan*/  P4_KEYINFO ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageEqNe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_6__*) ; 
 int /*<<< orphan*/ * sqlite3KeyInfoFromExprList (TYPE_6__*,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAppendP4 (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3WhereEnd (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void windowPartitionCache(
  Parse *pParse,
  Select *p,                      /* The rewritten SELECT statement */
  WhereInfo *pWInfo,              /* WhereInfo to call WhereEnd() on */
  int regFlushPart,               /* Register to use with Gosub lblFlushPart */
  int lblFlushPart,               /* Subroutine to Gosub to */
  int *pRegSize                   /* OUT: Register containing partition size */
){
  Window *pMWin = p->pWin;
  Vdbe *v = sqlite3GetVdbe(pParse);
  int iSubCsr = p->pSrc->a[0].iCursor;
  int nSub = p->pSrc->a[0].pTab->nCol;
  int k;

  int reg = pParse->nMem+1;
  int regRecord = reg+nSub;
  int regRowid = regRecord+1;

  *pRegSize = regRowid;
  pParse->nMem += nSub + 2;

  /* Load the column values for the row returned by the sub-select
  ** into an array of registers starting at reg. */
  for(k=0; k<nSub; k++){
    sqlite3VdbeAddOp3(v, OP_Column, iSubCsr, k, reg+k);
  }
  sqlite3VdbeAddOp3(v, OP_MakeRecord, reg, nSub, regRecord);

  /* Check if this is the start of a new partition. If so, call the
  ** flush_partition sub-routine.  */
  if( pMWin->pPartition ){
    int addr;
    ExprList *pPart = pMWin->pPartition;
    int nPart = pPart->nExpr;
    int regNewPart = reg + pMWin->nBufferCol;
    KeyInfo *pKeyInfo = sqlite3KeyInfoFromExprList(pParse, pPart, 0, 0);

    addr = sqlite3VdbeAddOp3(v, OP_Compare, regNewPart, pMWin->regPart,nPart);
    sqlite3VdbeAppendP4(v, (void*)pKeyInfo, P4_KEYINFO);
    sqlite3VdbeAddOp3(v, OP_Jump, addr+2, addr+4, addr+2);
    VdbeCoverageEqNe(v);
    sqlite3VdbeAddOp3(v, OP_Copy, regNewPart, pMWin->regPart, nPart-1);
    sqlite3VdbeAddOp2(v, OP_Gosub, regFlushPart, lblFlushPart);
    VdbeComment((v, "call flush_partition"));
  }

  /* Buffer the current row in the ephemeral table. */
  sqlite3VdbeAddOp2(v, OP_NewRowid, pMWin->iEphCsr, regRowid);
  sqlite3VdbeAddOp3(v, OP_Insert, pMWin->iEphCsr, regRecord, regRowid);

  /* End of the input loop */
  sqlite3WhereEnd(pWInfo);

  /* Invoke "flush_partition" to deal with the final (or only) partition */
  sqlite3VdbeAddOp2(v, OP_Gosub, regFlushPart, lblFlushPart);
  VdbeComment((v, "call flush_partition"));
}