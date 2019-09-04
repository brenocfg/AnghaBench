#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  size_t u16 ;
struct TYPE_6__ {int btsFlags; size_t usableSize; int pageSize; int /*<<< orphan*/  mutex; } ;
struct TYPE_5__ {unsigned char* aData; size_t hdrOffset; scalar_t__ pgno; size_t nFree; size_t cellOffset; unsigned char* aDataEnd; unsigned char* aCellIdx; unsigned char* aDataOfst; size_t childPtrSize; size_t maskPage; int isInit; scalar_t__ nCell; scalar_t__ nOverflow; int /*<<< orphan*/  pDbPage; TYPE_2__* pBt; } ;
typedef  TYPE_1__ MemPage ;
typedef  TYPE_2__ BtShared ;

/* Variables and functions */
 int BTS_FAST_SECURE ; 
 int PTF_LEAF ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  decodeFlags (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put2byte (unsigned char*,size_t) ; 
 unsigned char* sqlite3PagerGetData (int /*<<< orphan*/ ) ; 
 void* sqlite3PagerGetExtra (int /*<<< orphan*/ ) ; 
 int sqlite3PagerIswriteable (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3PagerPagenumber (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zeroPage(MemPage *pPage, int flags){
  unsigned char *data = pPage->aData;
  BtShared *pBt = pPage->pBt;
  u8 hdr = pPage->hdrOffset;
  u16 first;

  assert( sqlite3PagerPagenumber(pPage->pDbPage)==pPage->pgno );
  assert( sqlite3PagerGetExtra(pPage->pDbPage) == (void*)pPage );
  assert( sqlite3PagerGetData(pPage->pDbPage) == data );
  assert( sqlite3PagerIswriteable(pPage->pDbPage) );
  assert( sqlite3_mutex_held(pBt->mutex) );
  if( pBt->btsFlags & BTS_FAST_SECURE ){
    memset(&data[hdr], 0, pBt->usableSize - hdr);
  }
  data[hdr] = (char)flags;
  first = hdr + ((flags&PTF_LEAF)==0 ? 12 : 8);
  memset(&data[hdr+1], 0, 4);
  data[hdr+7] = 0;
  put2byte(&data[hdr+5], pBt->usableSize);
  pPage->nFree = (u16)(pBt->usableSize - first);
  decodeFlags(pPage, flags);
  pPage->cellOffset = first;
  pPage->aDataEnd = &data[pBt->usableSize];
  pPage->aCellIdx = &data[first];
  pPage->aDataOfst = &data[pPage->childPtrSize];
  pPage->nOverflow = 0;
  assert( pBt->pageSize>=512 && pBt->pageSize<=65536 );
  pPage->maskPage = (u16)(pBt->pageSize - 1);
  pPage->nCell = 0;
  pPage->isInit = 1;
}