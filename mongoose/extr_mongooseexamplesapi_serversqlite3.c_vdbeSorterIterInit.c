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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
struct TYPE_14__ {TYPE_1__* aDb; } ;
typedef  TYPE_2__ sqlite3 ;
typedef  int i64 ;
struct TYPE_15__ {int iReadOff; int nAlloc; int nBuffer; int iEof; int /*<<< orphan*/ * aBuffer; int /*<<< orphan*/ * aAlloc; int /*<<< orphan*/  pFile; } ;
typedef  TYPE_3__ VdbeSorterIter ;
struct TYPE_16__ {int iWriteOff; int /*<<< orphan*/  pTemp1; } ;
typedef  TYPE_4__ VdbeSorter ;
struct TYPE_13__ {int /*<<< orphan*/  pBt; } ;

/* Variables and functions */
 int SQLITE_IOERR_SHORT_READ ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3BtreeGetPageSize (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3DbMallocRaw (TYPE_2__*,int) ; 
 int sqlite3OsRead (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int vdbeSorterIterNext (TYPE_2__*,TYPE_3__*) ; 
 int vdbeSorterIterVarint (TYPE_2__*,TYPE_3__*,int*) ; 

__attribute__((used)) static int vdbeSorterIterInit(
  sqlite3 *db,                    /* Database handle */
  const VdbeSorter *pSorter,      /* Sorter object */
  i64 iStart,                     /* Start offset in pFile */
  VdbeSorterIter *pIter,          /* Iterator to populate */
  i64 *pnByte                     /* IN/OUT: Increment this value by PMA size */
){
  int rc = SQLITE_OK;
  int nBuf;

  nBuf = sqlite3BtreeGetPageSize(db->aDb[0].pBt);

  assert( pSorter->iWriteOff>iStart );
  assert( pIter->aAlloc==0 );
  assert( pIter->aBuffer==0 );
  pIter->pFile = pSorter->pTemp1;
  pIter->iReadOff = iStart;
  pIter->nAlloc = 128;
  pIter->aAlloc = (u8 *)sqlite3DbMallocRaw(db, pIter->nAlloc);
  pIter->nBuffer = nBuf;
  pIter->aBuffer = (u8 *)sqlite3DbMallocRaw(db, nBuf);

  if( !pIter->aBuffer ){
    rc = SQLITE_NOMEM;
  }else{
    int iBuf;

    iBuf = iStart % nBuf;
    if( iBuf ){
      int nRead = nBuf - iBuf;
      if( (iStart + nRead) > pSorter->iWriteOff ){
        nRead = (int)(pSorter->iWriteOff - iStart);
      }
      rc = sqlite3OsRead(
          pSorter->pTemp1, &pIter->aBuffer[iBuf], nRead, iStart
      );
      assert( rc!=SQLITE_IOERR_SHORT_READ );
    }

    if( rc==SQLITE_OK ){
      u64 nByte;                       /* Size of PMA in bytes */
      pIter->iEof = pSorter->iWriteOff;
      rc = vdbeSorterIterVarint(db, pIter, &nByte);
      pIter->iEof = pIter->iReadOff + nByte;
      *pnByte += nByte;
    }
  }

  if( rc==SQLITE_OK ){
    rc = vdbeSorterIterNext(db, pIter);
  }
  return rc;
}