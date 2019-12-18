#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_8__ ;
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_35__ {int nExpr; } ;
struct TYPE_34__ {int nMem; int /*<<< orphan*/  db; int /*<<< orphan*/  nTab; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_33__ {int nSelectRow; int iLimit; int iOffset; scalar_t__ op; int selFlags; int /*<<< orphan*/ * pLimit; TYPE_8__* pOrderBy; struct TYPE_33__* pPrior; struct TYPE_33__* pNext; void** addrOpenEphm; scalar_t__ pWin; TYPE_1__* pEList; TYPE_4__* pSrc; } ;
struct TYPE_32__ {TYPE_8__* pOrderBy; } ;
struct TYPE_31__ {int nSrc; TYPE_3__* a; } ;
struct TYPE_29__ {scalar_t__ isRecursive; } ;
struct TYPE_30__ {int iCursor; TYPE_2__ fg; } ;
struct TYPE_28__ {int nExpr; } ;
typedef  TYPE_4__ SrcList ;
typedef  TYPE_5__ SelectDest ;
typedef  TYPE_6__ Select ;
typedef  TYPE_7__ Parse ;
typedef  int /*<<< orphan*/  KeyInfo ;
typedef  TYPE_8__ ExprList ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 scalar_t__ ALWAYS (int) ; 
 int /*<<< orphan*/  ExplainQueryPlan (TYPE_7__*) ; 
 int /*<<< orphan*/  OP_Column ; 
 int /*<<< orphan*/  OP_DecrJumpZero ; 
 int /*<<< orphan*/  OP_Delete ; 
 int /*<<< orphan*/  OP_NullRow ; 
 int /*<<< orphan*/  OP_OpenEphemeral ; 
 int /*<<< orphan*/  OP_OpenPseudo ; 
 int /*<<< orphan*/  OP_Rewind ; 
 int /*<<< orphan*/  OP_RowData ; 
 int /*<<< orphan*/  P4_KEYINFO ; 
 int SF_Aggregate ; 
 int SF_UsesEphemeral ; 
 int /*<<< orphan*/  SQLITE_RECURSIVE ; 
 int SRT_DistFifo ; 
 int SRT_DistQueue ; 
 int SRT_Fifo ; 
 int SRT_Queue ; 
 scalar_t__ TK_UNION ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  codeOffset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  computeLimitRegisters (TYPE_7__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/ * multiSelectOrderByKeyInfo (TYPE_7__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  selectInnerLoop (TYPE_7__*,TYPE_6__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int,int) ; 
 scalar_t__ sqlite3AuthCheck (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ErrorMsg (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int sqlite3Select (TYPE_7__*,TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3SelectDestInit (TYPE_5__*,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeGoto (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeMakeLabel (TYPE_7__*) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void generateWithRecursiveQuery(
  Parse *pParse,        /* Parsing context */
  Select *p,            /* The recursive SELECT to be coded */
  SelectDest *pDest     /* What to do with query results */
){
  SrcList *pSrc = p->pSrc;      /* The FROM clause of the recursive query */
  int nCol = p->pEList->nExpr;  /* Number of columns in the recursive table */
  Vdbe *v = pParse->pVdbe;      /* The prepared statement under construction */
  Select *pSetup = p->pPrior;   /* The setup query */
  int addrTop;                  /* Top of the loop */
  int addrCont, addrBreak;      /* CONTINUE and BREAK addresses */
  int iCurrent = 0;             /* The Current table */
  int regCurrent;               /* Register holding Current table */
  int iQueue;                   /* The Queue table */
  int iDistinct = 0;            /* To ensure unique results if UNION */
  int eDest = SRT_Fifo;         /* How to write to Queue */
  SelectDest destQueue;         /* SelectDest targetting the Queue table */
  int i;                        /* Loop counter */
  int rc;                       /* Result code */
  ExprList *pOrderBy;           /* The ORDER BY clause */
  Expr *pLimit;                 /* Saved LIMIT and OFFSET */
  int regLimit, regOffset;      /* Registers used by LIMIT and OFFSET */

#ifndef SQLITE_OMIT_WINDOWFUNC
  if( p->pWin ){
    sqlite3ErrorMsg(pParse, "cannot use window functions in recursive queries");
    return;
  }
#endif

  /* Obtain authorization to do a recursive query */
  if( sqlite3AuthCheck(pParse, SQLITE_RECURSIVE, 0, 0, 0) ) return;

  /* Process the LIMIT and OFFSET clauses, if they exist */
  addrBreak = sqlite3VdbeMakeLabel(pParse);
  p->nSelectRow = 320;  /* 4 billion rows */
  computeLimitRegisters(pParse, p, addrBreak);
  pLimit = p->pLimit;
  regLimit = p->iLimit;
  regOffset = p->iOffset;
  p->pLimit = 0;
  p->iLimit = p->iOffset = 0;
  pOrderBy = p->pOrderBy;

  /* Locate the cursor number of the Current table */
  for(i=0; ALWAYS(i<pSrc->nSrc); i++){
    if( pSrc->a[i].fg.isRecursive ){
      iCurrent = pSrc->a[i].iCursor;
      break;
    }
  }

  /* Allocate cursors numbers for Queue and Distinct.  The cursor number for
  ** the Distinct table must be exactly one greater than Queue in order
  ** for the SRT_DistFifo and SRT_DistQueue destinations to work. */
  iQueue = pParse->nTab++;
  if( p->op==TK_UNION ){
    eDest = pOrderBy ? SRT_DistQueue : SRT_DistFifo;
    iDistinct = pParse->nTab++;
  }else{
    eDest = pOrderBy ? SRT_Queue : SRT_Fifo;
  }
  sqlite3SelectDestInit(&destQueue, eDest, iQueue);

  /* Allocate cursors for Current, Queue, and Distinct. */
  regCurrent = ++pParse->nMem;
  sqlite3VdbeAddOp3(v, OP_OpenPseudo, iCurrent, regCurrent, nCol);
  if( pOrderBy ){
    KeyInfo *pKeyInfo = multiSelectOrderByKeyInfo(pParse, p, 1);
    sqlite3VdbeAddOp4(v, OP_OpenEphemeral, iQueue, pOrderBy->nExpr+2, 0,
                      (char*)pKeyInfo, P4_KEYINFO);
    destQueue.pOrderBy = pOrderBy;
  }else{
    sqlite3VdbeAddOp2(v, OP_OpenEphemeral, iQueue, nCol);
  }
  VdbeComment((v, "Queue table"));
  if( iDistinct ){
    p->addrOpenEphm[0] = sqlite3VdbeAddOp2(v, OP_OpenEphemeral, iDistinct, 0);
    p->selFlags |= SF_UsesEphemeral;
  }

  /* Detach the ORDER BY clause from the compound SELECT */
  p->pOrderBy = 0;

  /* Store the results of the setup-query in Queue. */
  pSetup->pNext = 0;
  ExplainQueryPlan((pParse, 1, "SETUP"));
  rc = sqlite3Select(pParse, pSetup, &destQueue);
  pSetup->pNext = p;
  if( rc ) goto end_of_recursive_query;

  /* Find the next row in the Queue and output that row */
  addrTop = sqlite3VdbeAddOp2(v, OP_Rewind, iQueue, addrBreak); VdbeCoverage(v);

  /* Transfer the next row in Queue over to Current */
  sqlite3VdbeAddOp1(v, OP_NullRow, iCurrent); /* To reset column cache */
  if( pOrderBy ){
    sqlite3VdbeAddOp3(v, OP_Column, iQueue, pOrderBy->nExpr+1, regCurrent);
  }else{
    sqlite3VdbeAddOp2(v, OP_RowData, iQueue, regCurrent);
  }
  sqlite3VdbeAddOp1(v, OP_Delete, iQueue);

  /* Output the single row in Current */
  addrCont = sqlite3VdbeMakeLabel(pParse);
  codeOffset(v, regOffset, addrCont);
  selectInnerLoop(pParse, p, iCurrent,
      0, 0, pDest, addrCont, addrBreak);
  if( regLimit ){
    sqlite3VdbeAddOp2(v, OP_DecrJumpZero, regLimit, addrBreak);
    VdbeCoverage(v);
  }
  sqlite3VdbeResolveLabel(v, addrCont);

  /* Execute the recursive SELECT taking the single row in Current as
  ** the value for the recursive-table. Store the results in the Queue.
  */
  if( p->selFlags & SF_Aggregate ){
    sqlite3ErrorMsg(pParse, "recursive aggregate queries not supported");
  }else{
    p->pPrior = 0;
    ExplainQueryPlan((pParse, 1, "RECURSIVE STEP"));
    sqlite3Select(pParse, p, &destQueue);
    assert( p->pPrior==0 );
    p->pPrior = pSetup;
  }

  /* Keep running the loop until the Queue is empty */
  sqlite3VdbeGoto(v, addrTop);
  sqlite3VdbeResolveLabel(v, addrBreak);

end_of_recursive_query:
  sqlite3ExprListDelete(pParse->db, p->pOrderBy);
  p->pOrderBy = pOrderBy;
  p->pLimit = pLimit;
  return;
}