#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {scalar_t__ mallocFailed; TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_26__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  tnum; } ;
typedef  TYPE_3__ Table ;
struct TYPE_28__ {int tnum; int nKeyCol; int /*<<< orphan*/  zName; int /*<<< orphan*/  pSchema; TYPE_3__* pTable; } ;
struct TYPE_27__ {int /*<<< orphan*/  nTab; scalar_t__ nErr; TYPE_2__* db; } ;
struct TYPE_24__ {int /*<<< orphan*/  zDbSName; } ;
typedef  TYPE_4__ Parse ;
typedef  int /*<<< orphan*/  KeyInfo ;
typedef  TYPE_5__ Index ;

/* Variables and functions */
 scalar_t__ IsUniqueIndex (TYPE_5__*) ; 
 int /*<<< orphan*/  OE_Abort ; 
 int OPFLAG_BULKCSR ; 
 int OPFLAG_P2ISREG ; 
 int OPFLAG_USESEEKRESULT ; 
 int /*<<< orphan*/  OP_Clear ; 
 int /*<<< orphan*/  OP_Close ; 
 int /*<<< orphan*/  OP_IdxInsert ; 
 int /*<<< orphan*/  OP_Last ; 
 int /*<<< orphan*/  OP_Next ; 
 int /*<<< orphan*/  OP_OpenRead ; 
 int /*<<< orphan*/  OP_OpenWrite ; 
 int /*<<< orphan*/  OP_Rewind ; 
 int /*<<< orphan*/  OP_SorterCompare ; 
 int /*<<< orphan*/  OP_SorterData ; 
 int /*<<< orphan*/  OP_SorterInsert ; 
 int /*<<< orphan*/  OP_SorterNext ; 
 int /*<<< orphan*/  OP_SorterOpen ; 
 int /*<<< orphan*/  OP_SorterSort ; 
 int /*<<< orphan*/  P4_KEYINFO ; 
 int /*<<< orphan*/  SQLITE_REINDEX ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3AuthCheck (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3GenerateIndexKey (TYPE_4__*,TYPE_5__*,int,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3GetTempReg (TYPE_4__*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_4__*) ; 
 int /*<<< orphan*/ * sqlite3KeyInfoOfIndex (TYPE_4__*,TYPE_5__*) ; 
 scalar_t__ sqlite3KeyInfoRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3OpenTable (TYPE_4__*,int,int,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sqlite3ResolvePartIdxLabel (TYPE_4__*,int) ; 
 int sqlite3SchemaToIndex (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3TableLock (TYPE_4__*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3UniqueConstraint (TYPE_4__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4Int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int) ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeGoto (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void sqlite3RefillIndex(Parse *pParse, Index *pIndex, int memRootPage){
  Table *pTab = pIndex->pTable;  /* The table that is indexed */
  int iTab = pParse->nTab++;     /* Btree cursor used for pTab */
  int iIdx = pParse->nTab++;     /* Btree cursor used for pIndex */
  int iSorter;                   /* Cursor opened by OpenSorter (if in use) */
  int addr1;                     /* Address of top of loop */
  int addr2;                     /* Address to jump to for next iteration */
  int tnum;                      /* Root page of index */
  int iPartIdxLabel;             /* Jump to this label to skip a row */
  Vdbe *v;                       /* Generate code into this virtual machine */
  KeyInfo *pKey;                 /* KeyInfo for index */
  int regRecord;                 /* Register holding assembled index record */
  sqlite3 *db = pParse->db;      /* The database connection */
  int iDb = sqlite3SchemaToIndex(db, pIndex->pSchema);

#ifndef SQLITE_OMIT_AUTHORIZATION
  if( sqlite3AuthCheck(pParse, SQLITE_REINDEX, pIndex->zName, 0,
      db->aDb[iDb].zDbSName ) ){
    return;
  }
#endif

  /* Require a write-lock on the table to perform this operation */
  sqlite3TableLock(pParse, iDb, pTab->tnum, 1, pTab->zName);

  v = sqlite3GetVdbe(pParse);
  if( v==0 ) return;
  if( memRootPage>=0 ){
    tnum = memRootPage;
  }else{
    tnum = pIndex->tnum;
  }
  pKey = sqlite3KeyInfoOfIndex(pParse, pIndex);
  assert( pKey!=0 || db->mallocFailed || pParse->nErr );

  /* Open the sorter cursor if we are to use one. */
  iSorter = pParse->nTab++;
  sqlite3VdbeAddOp4(v, OP_SorterOpen, iSorter, 0, pIndex->nKeyCol, (char*)
                    sqlite3KeyInfoRef(pKey), P4_KEYINFO);

  /* Open the table. Loop through all rows of the table, inserting index
  ** records into the sorter. */
  sqlite3OpenTable(pParse, iTab, iDb, pTab, OP_OpenRead);
  addr1 = sqlite3VdbeAddOp2(v, OP_Rewind, iTab, 0); VdbeCoverage(v);
  regRecord = sqlite3GetTempReg(pParse);

  sqlite3GenerateIndexKey(pParse,pIndex,iTab,regRecord,0,&iPartIdxLabel,0,0);
  sqlite3VdbeAddOp2(v, OP_SorterInsert, iSorter, regRecord);
  sqlite3ResolvePartIdxLabel(pParse, iPartIdxLabel);
  sqlite3VdbeAddOp2(v, OP_Next, iTab, addr1+1); VdbeCoverage(v);
  sqlite3VdbeJumpHere(v, addr1);
  if( memRootPage<0 ) sqlite3VdbeAddOp2(v, OP_Clear, tnum, iDb);
  sqlite3VdbeAddOp4(v, OP_OpenWrite, iIdx, tnum, iDb,
                    (char *)pKey, P4_KEYINFO);
  sqlite3VdbeChangeP5(v, OPFLAG_BULKCSR|((memRootPage>=0)?OPFLAG_P2ISREG:0));

  addr1 = sqlite3VdbeAddOp2(v, OP_SorterSort, iSorter, 0); VdbeCoverage(v);
  if( IsUniqueIndex(pIndex) ){
    int j2 = sqlite3VdbeCurrentAddr(v) + 3;
    sqlite3VdbeGoto(v, j2);
    addr2 = sqlite3VdbeCurrentAddr(v);
    sqlite3VdbeAddOp4Int(v, OP_SorterCompare, iSorter, j2, regRecord,
                         pIndex->nKeyCol); VdbeCoverage(v);
    sqlite3UniqueConstraint(pParse, OE_Abort, pIndex);
  }else{
    addr2 = sqlite3VdbeCurrentAddr(v);
  }
  sqlite3VdbeAddOp3(v, OP_SorterData, iSorter, regRecord, iIdx);
  sqlite3VdbeAddOp3(v, OP_Last, iIdx, 0, -1);
  sqlite3VdbeAddOp2(v, OP_IdxInsert, iIdx, regRecord);
  sqlite3VdbeChangeP5(v, OPFLAG_USESEEKRESULT);
  sqlite3ReleaseTempReg(pParse, regRecord);
  sqlite3VdbeAddOp2(v, OP_SorterNext, iSorter, addr2); VdbeCoverage(v);
  sqlite3VdbeJumpHere(v, addr1);

  sqlite3VdbeAddOp1(v, OP_Close, iTab);
  sqlite3VdbeAddOp1(v, OP_Close, iIdx);
  sqlite3VdbeAddOp1(v, OP_Close, iSorter);
}