#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_7__ {int nSize; } ;
struct TYPE_6__ {size_t childPtrSize; int maxLocal; int minLocal; TYPE_1__* pBt; scalar_t__ hasData; scalar_t__ intKey; } ;
struct TYPE_5__ {int usableSize; } ;
typedef  TYPE_2__ MemPage ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_3__ debuginfo ; 
 int /*<<< orphan*/  getVarint32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static u16 cellSizePtr(MemPage *pPage, u8 *pCell){
  u8 *pIter = &pCell[pPage->childPtrSize];
  u32 nSize;

#ifdef SQLITE_DEBUG
  /* The value returned by this function should always be the same as
  ** the (CellInfo.nSize) value found by doing a full parse of the
  ** cell. If SQLITE_DEBUG is defined, an assert() at the bottom of
  ** this function verifies that this invariant is not violated. */
  CellInfo debuginfo;
  btreeParseCellPtr(pPage, pCell, &debuginfo);
#endif

  if( pPage->intKey ){
    u8 *pEnd;
    if( pPage->hasData ){
      pIter += getVarint32(pIter, nSize);
    }else{
      nSize = 0;
    }

    /* pIter now points at the 64-bit integer key value, a variable length 
    ** integer. The following block moves pIter to point at the first byte
    ** past the end of the key value. */
    pEnd = &pIter[9];
    while( (*pIter++)&0x80 && pIter<pEnd );
  }else{
    pIter += getVarint32(pIter, nSize);
  }

  testcase( nSize==pPage->maxLocal );
  testcase( nSize==pPage->maxLocal+1 );
  if( nSize>pPage->maxLocal ){
    int minLocal = pPage->minLocal;
    nSize = minLocal + (nSize - minLocal) % (pPage->pBt->usableSize - 4);
    testcase( nSize==pPage->maxLocal );
    testcase( nSize==pPage->maxLocal+1 );
    if( nSize>pPage->maxLocal ){
      nSize = minLocal;
    }
    nSize += 4;
  }
  nSize += (u32)(pIter - pCell);

  /* The minimum size of any cell is 4 bytes. */
  if( nSize<4 ){
    nSize = 4;
  }

  assert( nSize==debuginfo.nSize );
  return (u16)nSize;
}