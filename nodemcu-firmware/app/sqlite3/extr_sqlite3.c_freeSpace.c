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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_5__ {unsigned char* aData; int hdrOffset; int childPtrSize; int /*<<< orphan*/  nFree; TYPE_1__* pBt; int /*<<< orphan*/  pDbPage; } ;
struct TYPE_4__ {int usableSize; int btsFlags; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ MemPage ;

/* Variables and functions */
 int BTS_SECURE_DELETE ; 
 scalar_t__ CORRUPT_DB ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int get2byte (unsigned char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put2byte (unsigned char*,int) ; 
 int sqlite3PagerIswriteable (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int freeSpace(MemPage *pPage, u16 iStart, u16 iSize){
  u16 iPtr;                             /* Address of ptr to next freeblock */
  u16 iFreeBlk;                         /* Address of the next freeblock */
  u8 hdr;                               /* Page header size.  0 or 100 */
  u8 nFrag = 0;                         /* Reduction in fragmentation */
  u16 iOrigSize = iSize;                /* Original value of iSize */
  u32 iLast = pPage->pBt->usableSize-4; /* Largest possible freeblock offset */
  u32 iEnd = iStart + iSize;            /* First byte past the iStart buffer */
  unsigned char *data = pPage->aData;   /* Page content */

  assert( pPage->pBt!=0 );
  assert( sqlite3PagerIswriteable(pPage->pDbPage) );
  assert( CORRUPT_DB || iStart>=pPage->hdrOffset+6+pPage->childPtrSize );
  assert( CORRUPT_DB || iEnd <= pPage->pBt->usableSize );
  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  assert( iSize>=4 );   /* Minimum cell size is 4 */
  assert( iStart<=iLast );

  /* Overwrite deleted information with zeros when the secure_delete
  ** option is enabled */
  if( pPage->pBt->btsFlags & BTS_SECURE_DELETE ){
    memset(&data[iStart], 0, iSize);
  }

  /* The list of freeblocks must be in ascending order.  Find the
  ** spot on the list where iStart should be inserted.
  */
  hdr = pPage->hdrOffset;
  iPtr = hdr + 1;
  if( data[iPtr+1]==0 && data[iPtr]==0 ){
    iFreeBlk = 0;  /* Shortcut for the case when the freelist is empty */
  }else{
    while( (iFreeBlk = get2byte(&data[iPtr]))<iStart ){
      if( iFreeBlk<iPtr+4 ){
        if( iFreeBlk==0 ) break;
        return SQLITE_CORRUPT_BKPT;
      }
      iPtr = iFreeBlk;
    }
    if( iFreeBlk>iLast ) return SQLITE_CORRUPT_BKPT;
    assert( iFreeBlk>iPtr || iFreeBlk==0 );

    /* At this point:
    **    iFreeBlk:   First freeblock after iStart, or zero if none
    **    iPtr:       The address of a pointer to iFreeBlk
    **
    ** Check to see if iFreeBlk should be coalesced onto the end of iStart.
    */
    if( iFreeBlk && iEnd+3>=iFreeBlk ){
      nFrag = iFreeBlk - iEnd;
      if( iEnd>iFreeBlk ) return SQLITE_CORRUPT_BKPT;
      iEnd = iFreeBlk + get2byte(&data[iFreeBlk+2]);
      if( iEnd > pPage->pBt->usableSize ) return SQLITE_CORRUPT_BKPT;
      iSize = iEnd - iStart;
      iFreeBlk = get2byte(&data[iFreeBlk]);
    }

    /* If iPtr is another freeblock (that is, if iPtr is not the freelist
    ** pointer in the page header) then check to see if iStart should be
    ** coalesced onto the end of iPtr.
    */
    if( iPtr>hdr+1 ){
      int iPtrEnd = iPtr + get2byte(&data[iPtr+2]);
      if( iPtrEnd+3>=iStart ){
        if( iPtrEnd>iStart ) return SQLITE_CORRUPT_BKPT;
        nFrag += iStart - iPtrEnd;
        iSize = iEnd - iPtr;
        iStart = iPtr;
      }
    }
    if( nFrag>data[hdr+7] ) return SQLITE_CORRUPT_BKPT;
    data[hdr+7] -= nFrag;
  }
  if( iStart==get2byte(&data[hdr+5]) ){
    /* The new freeblock is at the beginning of the cell content area,
    ** so just extend the cell content area rather than create another
    ** freelist entry */
    if( iPtr!=hdr+1 ) return SQLITE_CORRUPT_BKPT;
    put2byte(&data[hdr+1], iFreeBlk);
    put2byte(&data[hdr+5], iEnd);
  }else{
    /* Insert the new freeblock into the freelist */
    put2byte(&data[iPtr], iStart);
    put2byte(&data[iStart], iFreeBlk);
    put2byte(&data[iStart+2], iSize);
  }
  pPage->nFree += iOrigSize;
  return SQLITE_OK;
}