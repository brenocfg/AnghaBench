#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_5__ {unsigned char* aData; int hdrOffset; int childPtrSize; int /*<<< orphan*/  pDbPage; TYPE_1__* pBt; scalar_t__ nFree; } ;
struct TYPE_4__ {int usableSize; int btsFlags; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ MemPage ;

/* Variables and functions */
 int BTS_SECURE_DELETE ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int get2byte (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put2byte (unsigned char*,int) ; 
 int sqlite3PagerIswriteable (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int freeSpace(MemPage *pPage, int start, int size){
  int addr, pbegin, hdr;
  int iLast;                        /* Largest possible freeblock offset */
  unsigned char *data = pPage->aData;

  assert( pPage->pBt!=0 );
  assert( sqlite3PagerIswriteable(pPage->pDbPage) );
  assert( start>=pPage->hdrOffset+6+pPage->childPtrSize );
  assert( (start + size) <= (int)pPage->pBt->usableSize );
  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  assert( size>=0 );   /* Minimum cell size is 4 */

  if( pPage->pBt->btsFlags & BTS_SECURE_DELETE ){
    /* Overwrite deleted information with zeros when the secure_delete
    ** option is enabled */
    memset(&data[start], 0, size);
  }

  /* Add the space back into the linked list of freeblocks.  Note that
  ** even though the freeblock list was checked by btreeInitPage(),
  ** btreeInitPage() did not detect overlapping cells or
  ** freeblocks that overlapped cells.   Nor does it detect when the
  ** cell content area exceeds the value in the page header.  If these
  ** situations arise, then subsequent insert operations might corrupt
  ** the freelist.  So we do need to check for corruption while scanning
  ** the freelist.
  */
  hdr = pPage->hdrOffset;
  addr = hdr + 1;
  iLast = pPage->pBt->usableSize - 4;
  assert( start<=iLast );
  while( (pbegin = get2byte(&data[addr]))<start && pbegin>0 ){
    if( pbegin<addr+4 ){
      return SQLITE_CORRUPT_BKPT;
    }
    addr = pbegin;
  }
  if( pbegin>iLast ){
    return SQLITE_CORRUPT_BKPT;
  }
  assert( pbegin>addr || pbegin==0 );
  put2byte(&data[addr], start);
  put2byte(&data[start], pbegin);
  put2byte(&data[start+2], size);
  pPage->nFree = pPage->nFree + (u16)size;

  /* Coalesce adjacent free blocks */
  addr = hdr + 1;
  while( (pbegin = get2byte(&data[addr]))>0 ){
    int pnext, psize, x;
    assert( pbegin>addr );
    assert( pbegin <= (int)pPage->pBt->usableSize-4 );
    pnext = get2byte(&data[pbegin]);
    psize = get2byte(&data[pbegin+2]);
    if( pbegin + psize + 3 >= pnext && pnext>0 ){
      int frag = pnext - (pbegin+psize);
      if( (frag<0) || (frag>(int)data[hdr+7]) ){
        return SQLITE_CORRUPT_BKPT;
      }
      data[hdr+7] -= (u8)frag;
      x = get2byte(&data[pnext]);
      put2byte(&data[pbegin], x);
      x = pnext + get2byte(&data[pnext+2]) - pbegin;
      put2byte(&data[pbegin+2], x);
    }else{
      addr = pbegin;
    }
  }

  /* If the cell content area begins with a freeblock, remove it. */
  if( data[hdr+1]==data[hdr+5] && data[hdr+2]==data[hdr+6] ){
    int top;
    pbegin = get2byte(&data[hdr+1]);
    memcpy(&data[hdr+1], &data[pbegin], 2);
    top = get2byte(&data[hdr+5]) + get2byte(&data[pbegin+2]);
    put2byte(&data[hdr+5], top);
  }
  assert( sqlite3PagerIswriteable(pPage->pDbPage) );
  return SQLITE_OK;
}