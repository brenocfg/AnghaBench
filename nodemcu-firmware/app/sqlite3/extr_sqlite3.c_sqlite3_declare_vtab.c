#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_28__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  mallocFailed; TYPE_5__* pVtabCtx; } ;
typedef  TYPE_4__ sqlite3 ;
struct TYPE_29__ {int bDeclared; TYPE_3__* pVTable; TYPE_6__* pTab; } ;
typedef  TYPE_5__ VtabCtx ;
struct TYPE_30__ {int tabFlags; TYPE_8__* pIndex; scalar_t__ aCol; scalar_t__ nCol; int /*<<< orphan*/  pSelect; } ;
typedef  TYPE_6__ Table ;
struct TYPE_32__ {scalar_t__ pNext; TYPE_6__* pTable; } ;
struct TYPE_31__ {int declareVtab; int nQueryLoop; TYPE_6__* pNewTable; scalar_t__ pVdbe; TYPE_4__* db; } ;
struct TYPE_27__ {TYPE_2__* pMod; } ;
struct TYPE_26__ {TYPE_1__* pModule; } ;
struct TYPE_25__ {scalar_t__ xUpdate; } ;
typedef  TYPE_7__ Parse ;
typedef  TYPE_8__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  HasRowid (TYPE_6__*) ; 
 int IsVirtual (TYPE_6__*) ; 
 int SQLITE_ERROR ; 
 int /*<<< orphan*/  SQLITE_MISUSE ; 
 int SQLITE_MISUSE_BKPT ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int TF_NoVisibleRowid ; 
 int TF_WithoutRowid ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3ApiExit (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  sqlite3DeleteTable (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  sqlite3Error (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ErrorWithMsg (TYPE_4__*,int,char*,char*) ; 
 int /*<<< orphan*/  sqlite3ParserReset (TYPE_7__*) ; 
 int sqlite3RunParser (TYPE_7__*,char const*,char**) ; 
 int /*<<< orphan*/  sqlite3SafetyCheckOk (TYPE_4__*) ; 
 TYPE_7__* sqlite3StackAllocZero (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sqlite3StackFree (TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  sqlite3VdbeFinalize (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

int sqlite3_declare_vtab(sqlite3 *db, const char *zCreateTable){
  VtabCtx *pCtx;
  Parse *pParse;
  int rc = SQLITE_OK;
  Table *pTab;
  char *zErr = 0;

#ifdef SQLITE_ENABLE_API_ARMOR
  if( !sqlite3SafetyCheckOk(db) || zCreateTable==0 ){
    return SQLITE_MISUSE_BKPT;
  }
#endif
  sqlite3_mutex_enter(db->mutex);
  pCtx = db->pVtabCtx;
  if( !pCtx || pCtx->bDeclared ){
    sqlite3Error(db, SQLITE_MISUSE);
    sqlite3_mutex_leave(db->mutex);
    return SQLITE_MISUSE_BKPT;
  }
  pTab = pCtx->pTab;
  assert( IsVirtual(pTab) );

  pParse = sqlite3StackAllocZero(db, sizeof(*pParse));
  if( pParse==0 ){
    rc = SQLITE_NOMEM_BKPT;
  }else{
    pParse->declareVtab = 1;
    pParse->db = db;
    pParse->nQueryLoop = 1;

    if( SQLITE_OK==sqlite3RunParser(pParse, zCreateTable, &zErr)
     && pParse->pNewTable
     && !db->mallocFailed
     && !pParse->pNewTable->pSelect
     && !IsVirtual(pParse->pNewTable)
    ){
      if( !pTab->aCol ){
        Table *pNew = pParse->pNewTable;
        Index *pIdx;
        pTab->aCol = pNew->aCol;
        pTab->nCol = pNew->nCol;
        pTab->tabFlags |= pNew->tabFlags & (TF_WithoutRowid|TF_NoVisibleRowid);
        pNew->nCol = 0;
        pNew->aCol = 0;
        assert( pTab->pIndex==0 );
        if( !HasRowid(pNew) && pCtx->pVTable->pMod->pModule->xUpdate!=0 ){
          rc = SQLITE_ERROR;
        }
        pIdx = pNew->pIndex;
        if( pIdx ){
          assert( pIdx->pNext==0 );
          pTab->pIndex = pIdx;
          pNew->pIndex = 0;
          pIdx->pTable = pTab;
        }
      }
      pCtx->bDeclared = 1;
    }else{
      sqlite3ErrorWithMsg(db, SQLITE_ERROR, (zErr ? "%s" : 0), zErr);
      sqlite3DbFree(db, zErr);
      rc = SQLITE_ERROR;
    }
    pParse->declareVtab = 0;

    if( pParse->pVdbe ){
      sqlite3VdbeFinalize(pParse->pVdbe);
    }
    sqlite3DeleteTable(db, pParse->pNewTable);
    sqlite3ParserReset(pParse);
    sqlite3StackFree(db, pParse);
  }

  assert( (rc&0xff)==rc );
  rc = sqlite3ApiExit(db, rc);
  sqlite3_mutex_leave(db->mutex);
  return rc;
}