#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_62__   TYPE_9__ ;
typedef  struct TYPE_61__   TYPE_8__ ;
typedef  struct TYPE_60__   TYPE_7__ ;
typedef  struct TYPE_59__   TYPE_6__ ;
typedef  struct TYPE_58__   TYPE_5__ ;
typedef  struct TYPE_57__   TYPE_4__ ;
typedef  struct TYPE_56__   TYPE_3__ ;
typedef  struct TYPE_55__   TYPE_2__ ;
typedef  struct TYPE_54__   TYPE_1__ ;
typedef  struct TYPE_53__   TYPE_17__ ;
typedef  struct TYPE_52__   TYPE_16__ ;
typedef  struct TYPE_51__   TYPE_15__ ;
typedef  struct TYPE_50__   TYPE_14__ ;
typedef  struct TYPE_49__   TYPE_13__ ;
typedef  struct TYPE_48__   TYPE_12__ ;
typedef  struct TYPE_47__   TYPE_11__ ;
typedef  struct TYPE_46__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_60__ {scalar_t__ viaCoroutine; } ;
struct SrcList_item {int colUsed; int regReturn; TYPE_7__ fg; int /*<<< orphan*/  regResult; TYPE_12__* pTab; int /*<<< orphan*/  addrFillSub; int /*<<< orphan*/  iCursor; } ;
struct TYPE_55__ {int leftColumn; } ;
struct TYPE_61__ {int wtFlags; TYPE_2__ u; TYPE_15__* pExpr; } ;
typedef  TYPE_8__ WhereTerm ;
struct TYPE_56__ {int nEq; TYPE_14__* pIndex; } ;
struct TYPE_57__ {TYPE_3__ btree; } ;
struct TYPE_62__ {scalar_t__ prereq; int nLTerm; int wsFlags; TYPE_4__ u; TYPE_8__** aLTerm; } ;
typedef  TYPE_9__ WhereLoop ;
struct TYPE_46__ {scalar_t__ iIdxCur; size_t iFrom; int iTabCur; TYPE_9__* pWLoop; } ;
typedef  TYPE_10__ WhereLevel ;
struct TYPE_47__ {size_t nTerm; TYPE_6__* pWInfo; TYPE_8__* a; } ;
typedef  TYPE_11__ WhereClause ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_48__ {int nCol; int /*<<< orphan*/  zName; TYPE_1__* aCol; } ;
typedef  TYPE_12__ Table ;
struct TYPE_59__ {TYPE_5__* pTabList; } ;
struct TYPE_58__ {struct SrcList_item* a; } ;
struct TYPE_54__ {int /*<<< orphan*/  zName; } ;
struct TYPE_53__ {int mallocFailed; } ;
struct TYPE_52__ {void* zName; } ;
struct TYPE_51__ {int /*<<< orphan*/  pRight; int /*<<< orphan*/  pLeft; int /*<<< orphan*/  iRightJoinTable; } ;
struct TYPE_50__ {char* zName; int* aiColumn; void** azColl; TYPE_12__* pTable; } ;
struct TYPE_49__ {TYPE_17__* db; int /*<<< orphan*/  nTab; int /*<<< orphan*/ * pVdbe; } ;
typedef  TYPE_13__ Parse ;
typedef  TYPE_14__ Index ;
typedef  TYPE_15__ Expr ;
typedef  TYPE_16__ CollSeq ;
typedef  int Bitmask ;

/* Variables and functions */
 int BMS ; 
 int /*<<< orphan*/  EP_FromJoin ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_15__*,int /*<<< orphan*/ ) ; 
 int MASKBIT (int) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  OPFLAG_USESEEKRESULT ; 
 int /*<<< orphan*/  OP_IdxInsert ; 
 int /*<<< orphan*/  OP_InitCoroutine ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  OP_Next ; 
 int /*<<< orphan*/  OP_Once ; 
 int /*<<< orphan*/  OP_OpenAutoindex ; 
 int /*<<< orphan*/  OP_Rewind ; 
 int /*<<< orphan*/  OP_Yield ; 
 int /*<<< orphan*/  SQLITE_JUMPIFNULL ; 
 int /*<<< orphan*/  SQLITE_STMTSTATUS_AUTOINDEX ; 
 int /*<<< orphan*/  SQLITE_WARNING_AUTOINDEX ; 
 int TERM_VIRTUAL ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int WHERE_AUTO_INDEX ; 
 int WHERE_COLUMN_EQ ; 
 int WHERE_IDX_ONLY ; 
 int WHERE_INDEXED ; 
 int WHERE_PARTIALIDX ; 
 int XN_ROWID ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_14__* sqlite3AllocateIndexObject (TYPE_17__*,int,int /*<<< orphan*/ ,char**) ; 
 TYPE_16__* sqlite3BinaryCompareCollSeq (TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_15__* sqlite3ExprAnd (TYPE_17__*,TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (TYPE_17__*,TYPE_15__*) ; 
 int /*<<< orphan*/  sqlite3ExprDup (TYPE_17__*,TYPE_15__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprIfFalse (TYPE_13__*,TYPE_15__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3ExprIsTableConstant (TYPE_15__*,int /*<<< orphan*/ ) ; 
 int sqlite3GenerateIndexKey (TYPE_13__*,TYPE_14__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3GetTempReg (TYPE_13__*) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_13__*,int) ; 
 void* sqlite3StrBINARY ; 
 int sqlite3VdbeAddOp0 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP2 (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeGoto (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeMakeLabel (TYPE_13__*) ; 
 int /*<<< orphan*/  sqlite3VdbeResolveLabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeSetP4KeyInfo (TYPE_13__*,TYPE_14__*) ; 
 int /*<<< orphan*/  sqlite3_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ termCanDriveIndex (TYPE_8__*,struct SrcList_item*,int) ; 
 int /*<<< orphan*/  testcase (int) ; 
 int /*<<< orphan*/  translateColumnToCopy (TYPE_13__*,int,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ whereLoopResize (TYPE_17__*,TYPE_9__*,int) ; 

__attribute__((used)) static void constructAutomaticIndex(
  Parse *pParse,              /* The parsing context */
  WhereClause *pWC,           /* The WHERE clause */
  struct SrcList_item *pSrc,  /* The FROM clause term to get the next index */
  Bitmask notReady,           /* Mask of cursors that are not available */
  WhereLevel *pLevel          /* Write new index here */
){
  int nKeyCol;                /* Number of columns in the constructed index */
  WhereTerm *pTerm;           /* A single term of the WHERE clause */
  WhereTerm *pWCEnd;          /* End of pWC->a[] */
  Index *pIdx;                /* Object describing the transient index */
  Vdbe *v;                    /* Prepared statement under construction */
  int addrInit;               /* Address of the initialization bypass jump */
  Table *pTable;              /* The table being indexed */
  int addrTop;                /* Top of the index fill loop */
  int regRecord;              /* Register holding an index record */
  int n;                      /* Column counter */
  int i;                      /* Loop counter */
  int mxBitCol;               /* Maximum column in pSrc->colUsed */
  CollSeq *pColl;             /* Collating sequence to on a column */
  WhereLoop *pLoop;           /* The Loop object */
  char *zNotUsed;             /* Extra space on the end of pIdx */
  Bitmask idxCols;            /* Bitmap of columns used for indexing */
  Bitmask extraCols;          /* Bitmap of additional columns */
  u8 sentWarning = 0;         /* True if a warnning has been issued */
  Expr *pPartial = 0;         /* Partial Index Expression */
  int iContinue = 0;          /* Jump here to skip excluded rows */
  struct SrcList_item *pTabItem;  /* FROM clause term being indexed */
  int addrCounter = 0;        /* Address where integer counter is initialized */
  int regBase;                /* Array of registers where record is assembled */

  /* Generate code to skip over the creation and initialization of the
  ** transient index on 2nd and subsequent iterations of the loop. */
  v = pParse->pVdbe;
  assert( v!=0 );
  addrInit = sqlite3VdbeAddOp0(v, OP_Once); VdbeCoverage(v);

  /* Count the number of columns that will be added to the index
  ** and used to match WHERE clause constraints */
  nKeyCol = 0;
  pTable = pSrc->pTab;
  pWCEnd = &pWC->a[pWC->nTerm];
  pLoop = pLevel->pWLoop;
  idxCols = 0;
  for(pTerm=pWC->a; pTerm<pWCEnd; pTerm++){
    Expr *pExpr = pTerm->pExpr;
    assert( !ExprHasProperty(pExpr, EP_FromJoin)    /* prereq always non-zero */
         || pExpr->iRightJoinTable!=pSrc->iCursor   /*   for the right-hand   */
         || pLoop->prereq!=0 );                     /*   table of a LEFT JOIN */
    if( pLoop->prereq==0
     && (pTerm->wtFlags & TERM_VIRTUAL)==0
     && !ExprHasProperty(pExpr, EP_FromJoin)
     && sqlite3ExprIsTableConstant(pExpr, pSrc->iCursor) ){
      pPartial = sqlite3ExprAnd(pParse->db, pPartial,
                                sqlite3ExprDup(pParse->db, pExpr, 0));
    }
    if( termCanDriveIndex(pTerm, pSrc, notReady) ){
      int iCol = pTerm->u.leftColumn;
      Bitmask cMask = iCol>=BMS ? MASKBIT(BMS-1) : MASKBIT(iCol);
      testcase( iCol==BMS );
      testcase( iCol==BMS-1 );
      if( !sentWarning ){
        sqlite3_log(SQLITE_WARNING_AUTOINDEX,
            "automatic index on %s(%s)", pTable->zName,
            pTable->aCol[iCol].zName);
        sentWarning = 1;
      }
      if( (idxCols & cMask)==0 ){
        if( whereLoopResize(pParse->db, pLoop, nKeyCol+1) ){
          goto end_auto_index_create;
        }
        pLoop->aLTerm[nKeyCol++] = pTerm;
        idxCols |= cMask;
      }
    }
  }
  assert( nKeyCol>0 );
  pLoop->u.btree.nEq = pLoop->nLTerm = nKeyCol;
  pLoop->wsFlags = WHERE_COLUMN_EQ | WHERE_IDX_ONLY | WHERE_INDEXED
                     | WHERE_AUTO_INDEX;

  /* Count the number of additional columns needed to create a
  ** covering index.  A "covering index" is an index that contains all
  ** columns that are needed by the query.  With a covering index, the
  ** original table never needs to be accessed.  Automatic indices must
  ** be a covering index because the index will not be updated if the
  ** original table changes and the index and table cannot both be used
  ** if they go out of sync.
  */
  extraCols = pSrc->colUsed & (~idxCols | MASKBIT(BMS-1));
  mxBitCol = MIN(BMS-1,pTable->nCol);
  testcase( pTable->nCol==BMS-1 );
  testcase( pTable->nCol==BMS-2 );
  for(i=0; i<mxBitCol; i++){
    if( extraCols & MASKBIT(i) ) nKeyCol++;
  }
  if( pSrc->colUsed & MASKBIT(BMS-1) ){
    nKeyCol += pTable->nCol - BMS + 1;
  }

  /* Construct the Index object to describe this index */
  pIdx = sqlite3AllocateIndexObject(pParse->db, nKeyCol+1, 0, &zNotUsed);
  if( pIdx==0 ) goto end_auto_index_create;
  pLoop->u.btree.pIndex = pIdx;
  pIdx->zName = "auto-index";
  pIdx->pTable = pTable;
  n = 0;
  idxCols = 0;
  for(pTerm=pWC->a; pTerm<pWCEnd; pTerm++){
    if( termCanDriveIndex(pTerm, pSrc, notReady) ){
      int iCol = pTerm->u.leftColumn;
      Bitmask cMask = iCol>=BMS ? MASKBIT(BMS-1) : MASKBIT(iCol);
      testcase( iCol==BMS-1 );
      testcase( iCol==BMS );
      if( (idxCols & cMask)==0 ){
        Expr *pX = pTerm->pExpr;
        idxCols |= cMask;
        pIdx->aiColumn[n] = pTerm->u.leftColumn;
        pColl = sqlite3BinaryCompareCollSeq(pParse, pX->pLeft, pX->pRight);
        pIdx->azColl[n] = pColl ? pColl->zName : sqlite3StrBINARY;
        n++;
      }
    }
  }
  assert( (u32)n==pLoop->u.btree.nEq );

  /* Add additional columns needed to make the automatic index into
  ** a covering index */
  for(i=0; i<mxBitCol; i++){
    if( extraCols & MASKBIT(i) ){
      pIdx->aiColumn[n] = i;
      pIdx->azColl[n] = sqlite3StrBINARY;
      n++;
    }
  }
  if( pSrc->colUsed & MASKBIT(BMS-1) ){
    for(i=BMS-1; i<pTable->nCol; i++){
      pIdx->aiColumn[n] = i;
      pIdx->azColl[n] = sqlite3StrBINARY;
      n++;
    }
  }
  assert( n==nKeyCol );
  pIdx->aiColumn[n] = XN_ROWID;
  pIdx->azColl[n] = sqlite3StrBINARY;

  /* Create the automatic index */
  assert( pLevel->iIdxCur>=0 );
  pLevel->iIdxCur = pParse->nTab++;
  sqlite3VdbeAddOp2(v, OP_OpenAutoindex, pLevel->iIdxCur, nKeyCol+1);
  sqlite3VdbeSetP4KeyInfo(pParse, pIdx);
  VdbeComment((v, "for %s", pTable->zName));

  /* Fill the automatic index with content */
  pTabItem = &pWC->pWInfo->pTabList->a[pLevel->iFrom];
  if( pTabItem->fg.viaCoroutine ){
    int regYield = pTabItem->regReturn;
    addrCounter = sqlite3VdbeAddOp2(v, OP_Integer, 0, 0);
    sqlite3VdbeAddOp3(v, OP_InitCoroutine, regYield, 0, pTabItem->addrFillSub);
    addrTop =  sqlite3VdbeAddOp1(v, OP_Yield, regYield);
    VdbeCoverage(v);
    VdbeComment((v, "next row of %s", pTabItem->pTab->zName));
  }else{
    addrTop = sqlite3VdbeAddOp1(v, OP_Rewind, pLevel->iTabCur); VdbeCoverage(v);
  }
  if( pPartial ){
    iContinue = sqlite3VdbeMakeLabel(pParse);
    sqlite3ExprIfFalse(pParse, pPartial, iContinue, SQLITE_JUMPIFNULL);
    pLoop->wsFlags |= WHERE_PARTIALIDX;
  }
  regRecord = sqlite3GetTempReg(pParse);
  regBase = sqlite3GenerateIndexKey(
      pParse, pIdx, pLevel->iTabCur, regRecord, 0, 0, 0, 0
  );
  sqlite3VdbeAddOp2(v, OP_IdxInsert, pLevel->iIdxCur, regRecord);
  sqlite3VdbeChangeP5(v, OPFLAG_USESEEKRESULT);
  if( pPartial ) sqlite3VdbeResolveLabel(v, iContinue);
  if( pTabItem->fg.viaCoroutine ){
    sqlite3VdbeChangeP2(v, addrCounter, regBase+n);
    testcase( pParse->db->mallocFailed );
    translateColumnToCopy(pParse, addrTop, pLevel->iTabCur,
                          pTabItem->regResult, 1);
    sqlite3VdbeGoto(v, addrTop);
    pTabItem->fg.viaCoroutine = 0;
  }else{
    sqlite3VdbeAddOp2(v, OP_Next, pLevel->iTabCur, addrTop+1); VdbeCoverage(v);
  }
  sqlite3VdbeChangeP5(v, SQLITE_STMTSTATUS_AUTOINDEX);
  sqlite3VdbeJumpHere(v, addrTop);
  sqlite3ReleaseTempReg(pParse, regRecord);
  
  /* Jump here when skipping the initialization */
  sqlite3VdbeJumpHere(v, addrInit);

end_auto_index_create:
  sqlite3ExprDelete(pParse->db, pPartial);
}