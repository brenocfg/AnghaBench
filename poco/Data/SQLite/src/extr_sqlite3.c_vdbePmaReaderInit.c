#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ i64 ;
struct TYPE_10__ {scalar_t__ aAlloc; scalar_t__ nAlloc; scalar_t__ aBuffer; scalar_t__ aMap; scalar_t__ iReadOff; scalar_t__ iEof; } ;
struct TYPE_9__ {scalar_t__ iEof; } ;
typedef  TYPE_1__ SorterFile ;
typedef  int /*<<< orphan*/  SortSubtask ;
typedef  TYPE_2__ PmaReader ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int vdbePmaReadVarint (TYPE_2__*,scalar_t__*) ; 
 int vdbePmaReaderNext (TYPE_2__*) ; 
 int vdbePmaReaderSeek (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int vdbePmaReaderInit(
  SortSubtask *pTask,             /* Task context */
  SorterFile *pFile,              /* Sorter file to read from */
  i64 iStart,                     /* Start offset in pFile */
  PmaReader *pReadr,              /* PmaReader to populate */
  i64 *pnByte                     /* IN/OUT: Increment this value by PMA size */
){
  int rc;

  assert( pFile->iEof>iStart );
  assert( pReadr->aAlloc==0 && pReadr->nAlloc==0 );
  assert( pReadr->aBuffer==0 );
  assert( pReadr->aMap==0 );

  rc = vdbePmaReaderSeek(pTask, pReadr, pFile, iStart);
  if( rc==SQLITE_OK ){
    u64 nByte = 0;                 /* Size of PMA in bytes */
    rc = vdbePmaReadVarint(pReadr, &nByte);
    pReadr->iEof = pReadr->iReadOff + nByte;
    *pnByte += nByte;
  }

  if( rc==SQLITE_OK ){
    rc = vdbePmaReaderNext(pReadr);
  }
  return rc;
}