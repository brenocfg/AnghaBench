#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ValueNewStat4Ctx {int iVal; TYPE_2__** ppRec; int /*<<< orphan*/  pParse; TYPE_4__* pIdx; } ;
struct TYPE_10__ {int /*<<< orphan*/ * db; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_11__ {int nField; TYPE_1__* aMem; TYPE_7__* pKeyInfo; } ;
typedef  TYPE_2__ UnpackedRecord ;
struct TYPE_13__ {int nAllField; scalar_t__ enc; } ;
struct TYPE_12__ {int nColumn; } ;
typedef  TYPE_1__ Mem ;
typedef  TYPE_4__ Index ;

/* Variables and functions */
 scalar_t__ ENC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEM_Null ; 
 int ROUND8 (int) ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (struct ValueNewStat4Ctx*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3DbFreeNN (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ sqlite3DbMallocZero (int /*<<< orphan*/ *,int) ; 
 TYPE_7__* sqlite3KeyInfoOfIndex (int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_1__* sqlite3ValueNew (int /*<<< orphan*/ *) ; 

__attribute__((used)) static sqlite3_value *valueNew(sqlite3 *db, struct ValueNewStat4Ctx *p){
#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
  if( p ){
    UnpackedRecord *pRec = p->ppRec[0];

    if( pRec==0 ){
      Index *pIdx = p->pIdx;      /* Index being probed */
      int nByte;                  /* Bytes of space to allocate */
      int i;                      /* Counter variable */
      int nCol = pIdx->nColumn;   /* Number of index columns including rowid */
  
      nByte = sizeof(Mem) * nCol + ROUND8(sizeof(UnpackedRecord));
      pRec = (UnpackedRecord*)sqlite3DbMallocZero(db, nByte);
      if( pRec ){
        pRec->pKeyInfo = sqlite3KeyInfoOfIndex(p->pParse, pIdx);
        if( pRec->pKeyInfo ){
          assert( pRec->pKeyInfo->nAllField==nCol );
          assert( pRec->pKeyInfo->enc==ENC(db) );
          pRec->aMem = (Mem *)((u8*)pRec + ROUND8(sizeof(UnpackedRecord)));
          for(i=0; i<nCol; i++){
            pRec->aMem[i].flags = MEM_Null;
            pRec->aMem[i].db = db;
          }
        }else{
          sqlite3DbFreeNN(db, pRec);
          pRec = 0;
        }
      }
      if( pRec==0 ) return 0;
      p->ppRec[0] = pRec;
    }
  
    pRec->nField = p->iVal+1;
    return &pRec->aMem[p->iVal];
  }
#else
  UNUSED_PARAMETER(p);
#endif /* defined(SQLITE_ENABLE_STAT3_OR_STAT4) */
  return sqlite3ValueNew(db);
}