#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i64 ;
struct TYPE_12__ {scalar_t__ nField; } ;
typedef  TYPE_1__ UnpackedRecord ;
struct TYPE_14__ {TYPE_2__* pKeyInfo; } ;
struct TYPE_13__ {scalar_t__ nAllField; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ KeyInfo ;
typedef  TYPE_3__ BtCursor ;

/* Variables and functions */
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_NOMEM_BKPT ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3BtreeMovetoUnpacked (TYPE_3__*,TYPE_1__*,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* sqlite3VdbeAllocUnpackedRecord (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VdbeRecordUnpack (TYPE_2__*,int,void const*,TYPE_1__*) ; 

__attribute__((used)) static int btreeMoveto(
  BtCursor *pCur,     /* Cursor open on the btree to be searched */
  const void *pKey,   /* Packed key if the btree is an index */
  i64 nKey,           /* Integer key for tables.  Size of pKey for indices */
  int bias,           /* Bias search to the high end */
  int *pRes           /* Write search results here */
){
  int rc;                    /* Status code */
  UnpackedRecord *pIdxKey;   /* Unpacked index key */

  if( pKey ){
    KeyInfo *pKeyInfo = pCur->pKeyInfo;
    assert( nKey==(i64)(int)nKey );
    pIdxKey = sqlite3VdbeAllocUnpackedRecord(pKeyInfo);
    if( pIdxKey==0 ) return SQLITE_NOMEM_BKPT;
    sqlite3VdbeRecordUnpack(pKeyInfo, (int)nKey, pKey, pIdxKey);
    if( pIdxKey->nField==0 || pIdxKey->nField>pKeyInfo->nAllField ){
      rc = SQLITE_CORRUPT_BKPT;
      goto moveto_done;
    }
  }else{
    pIdxKey = 0;
  }
  rc = sqlite3BtreeMovetoUnpacked(pCur, pIdxKey, nKey, bias, pRes);
moveto_done:
  if( pIdxKey ){
    sqlite3DbFree(pCur->pKeyInfo->db, pIdxKey);
  }
  return rc;
}