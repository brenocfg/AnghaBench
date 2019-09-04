#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_7__ {scalar_t__ nInMemory; scalar_t__ pRecord; scalar_t__ pTemp1; scalar_t__ iWriteOff; scalar_t__ nPMA; } ;
typedef  TYPE_1__ VdbeSorter ;
struct TYPE_8__ {TYPE_1__* pSorter; } ;
typedef  TYPE_2__ VdbeCursor ;
struct TYPE_9__ {scalar_t__ nVal; int /*<<< orphan*/  pVal; struct TYPE_9__* pNext; } ;
typedef  TYPE_3__ SorterRecord ;
typedef  int /*<<< orphan*/  FileWriter ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int fileWriterFinish (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  fileWriterInit (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fileWriterWrite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fileWriterWriteVarint (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int vdbeSorterOpenTempFile (int /*<<< orphan*/ *,scalar_t__*) ; 
 int vdbeSorterSort (TYPE_2__ const*) ; 

__attribute__((used)) static int vdbeSorterListToPMA(sqlite3 *db, const VdbeCursor *pCsr){
  int rc = SQLITE_OK;             /* Return code */
  VdbeSorter *pSorter = pCsr->pSorter;
  FileWriter writer;

  memset(&writer, 0, sizeof(FileWriter));

  if( pSorter->nInMemory==0 ){
    assert( pSorter->pRecord==0 );
    return rc;
  }

  rc = vdbeSorterSort(pCsr);

  /* If the first temporary PMA file has not been opened, open it now. */
  if( rc==SQLITE_OK && pSorter->pTemp1==0 ){
    rc = vdbeSorterOpenTempFile(db, &pSorter->pTemp1);
    assert( rc!=SQLITE_OK || pSorter->pTemp1 );
    assert( pSorter->iWriteOff==0 );
    assert( pSorter->nPMA==0 );
  }

  if( rc==SQLITE_OK ){
    SorterRecord *p;
    SorterRecord *pNext = 0;

    fileWriterInit(db, pSorter->pTemp1, &writer, pSorter->iWriteOff);
    pSorter->nPMA++;
    fileWriterWriteVarint(&writer, pSorter->nInMemory);
    for(p=pSorter->pRecord; p; p=pNext){
      pNext = p->pNext;
      fileWriterWriteVarint(&writer, p->nVal);
      fileWriterWrite(&writer, p->pVal, p->nVal);
      sqlite3DbFree(db, p);
    }
    pSorter->pRecord = p;
    rc = fileWriterFinish(db, &writer, &pSorter->iWriteOff);
  }

  return rc;
}