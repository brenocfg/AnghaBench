#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {int nCell; int hdrOffset; int nFree; int /*<<< orphan*/ * aCellIdx; TYPE_1__* pBt; int /*<<< orphan*/ * aData; int /*<<< orphan*/  pDbPage; } ;
struct TYPE_6__ {scalar_t__ usableSize; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ MemPage ;

/* Variables and functions */
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_PTR_TO_INT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int cellSize (TYPE_2__*,int) ; 
 int freeSpace (TYPE_2__*,scalar_t__,int) ; 
 scalar_t__ get2byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put2byte (int /*<<< orphan*/ *,int) ; 
 int sqlite3PagerIswriteable (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void dropCell(MemPage *pPage, int idx, int sz, int *pRC){
  u32 pc;         /* Offset to cell content of cell being deleted */
  u8 *data;       /* pPage->aData */
  u8 *ptr;        /* Used to move bytes around within data[] */
  u8 *endPtr;     /* End of loop */
  int rc;         /* The return code */
  int hdr;        /* Beginning of the header.  0 most pages.  100 page 1 */

  if( *pRC ) return;

  assert( idx>=0 && idx<pPage->nCell );
  assert( sz==cellSize(pPage, idx) );
  assert( sqlite3PagerIswriteable(pPage->pDbPage) );
  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  data = pPage->aData;
  ptr = &pPage->aCellIdx[2*idx];
  pc = get2byte(ptr);
  hdr = pPage->hdrOffset;
  testcase( pc==get2byte(&data[hdr+5]) );
  testcase( pc+sz==pPage->pBt->usableSize );
  if( pc < (u32)get2byte(&data[hdr+5]) || pc+sz > pPage->pBt->usableSize ){
    *pRC = SQLITE_CORRUPT_BKPT;
    return;
  }
  rc = freeSpace(pPage, pc, sz);
  if( rc ){
    *pRC = rc;
    return;
  }
  endPtr = &pPage->aCellIdx[2*pPage->nCell - 2];
  assert( (SQLITE_PTR_TO_INT(ptr)&1)==0 );  /* ptr is always 2-byte aligned */
  while( ptr<endPtr ){
    *(u16*)ptr = *(u16*)&ptr[2];
    ptr += 2;
  }
  pPage->nCell--;
  put2byte(&data[hdr+3], pPage->nCell);
  pPage->nFree += 2;
}