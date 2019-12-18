#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_18__ {size_t pageSize; int usableSize; scalar_t__ autoVacuum; int /*<<< orphan*/  mutex; } ;
struct TYPE_17__ {int nData; int nZero; int nKey; int /*<<< orphan*/ * pKey; int /*<<< orphan*/ * pData; } ;
struct TYPE_16__ {unsigned char* pPayload; int nKey; int nSize; int nLocal; } ;
struct TYPE_15__ {unsigned char* aData; int childPtrSize; int maxLocal; int minLocal; int /*<<< orphan*/  pDbPage; int /*<<< orphan*/  (* xParseCell ) (TYPE_1__*,unsigned char*,TYPE_2__*) ;TYPE_4__* pBt; int /*<<< orphan*/  const* intKeyLeaf; scalar_t__ intKey; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_1__ MemPage ;
typedef  TYPE_2__ CellInfo ;
typedef  TYPE_3__ BtreePayload ;
typedef  TYPE_4__ BtShared ;

/* Variables and functions */
 scalar_t__ PENDING_BYTE_PAGE (TYPE_4__*) ; 
 scalar_t__ PTRMAP_ISPAGE (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  PTRMAP_OVERFLOW1 ; 
 int /*<<< orphan*/  PTRMAP_OVERFLOW2 ; 
 int SQLITE_OK ; 
 int allocateBtreePage (TYPE_4__*,TYPE_1__**,scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptrmapPut (TYPE_4__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  put4byte (unsigned char*,scalar_t__) ; 
 scalar_t__ putVarint (unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ putVarint32 (unsigned char*,int) ; 
 int /*<<< orphan*/  releasePage (TYPE_1__*) ; 
 scalar_t__ sqlite3PagerIswriteable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,unsigned char*,TYPE_2__*) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int fillInCell(
  MemPage *pPage,                /* The page that contains the cell */
  unsigned char *pCell,          /* Complete text of the cell */
  const BtreePayload *pX,        /* Payload with which to construct the cell */
  int *pnSize                    /* Write cell size here */
){
  int nPayload;
  const u8 *pSrc;
  int nSrc, n, rc;
  int spaceLeft;
  MemPage *pOvfl = 0;
  MemPage *pToRelease = 0;
  unsigned char *pPrior;
  unsigned char *pPayload;
  BtShared *pBt = pPage->pBt;
  Pgno pgnoOvfl = 0;
  int nHeader;

  assert( sqlite3_mutex_held(pPage->pBt->mutex) );

  /* pPage is not necessarily writeable since pCell might be auxiliary
  ** buffer space that is separate from the pPage buffer area */
  assert( pCell<pPage->aData || pCell>=&pPage->aData[pBt->pageSize]
            || sqlite3PagerIswriteable(pPage->pDbPage) );

  /* Fill in the header. */
  nHeader = pPage->childPtrSize;
  if( pPage->intKey ){
    nPayload = pX->nData + pX->nZero;
    pSrc = pX->pData;
    nSrc = pX->nData;
    assert( pPage->intKeyLeaf ); /* fillInCell() only called for leaves */
    nHeader += putVarint32(&pCell[nHeader], nPayload);
    nHeader += putVarint(&pCell[nHeader], *(u64*)&pX->nKey);
  }else{
    assert( pX->nKey<=0x7fffffff && pX->pKey!=0 );
    nSrc = nPayload = (int)pX->nKey;
    pSrc = pX->pKey;
    nHeader += putVarint32(&pCell[nHeader], nPayload);
  }

  /* Fill in the payload */
  if( nPayload<=pPage->maxLocal ){
    n = nHeader + nPayload;
    testcase( n==3 );
    testcase( n==4 );
    if( n<4 ) n = 4;
    *pnSize = n;
    spaceLeft = nPayload;
    pPrior = pCell;
  }else{
    int mn = pPage->minLocal;
    n = mn + (nPayload - mn) % (pPage->pBt->usableSize - 4);
    testcase( n==pPage->maxLocal );
    testcase( n==pPage->maxLocal+1 );
    if( n > pPage->maxLocal ) n = mn;
    spaceLeft = n;
    *pnSize = n + nHeader + 4;
    pPrior = &pCell[nHeader+n];
  }
  pPayload = &pCell[nHeader];

  /* At this point variables should be set as follows:
  **
  **   nPayload           Total payload size in bytes
  **   pPayload           Begin writing payload here
  **   spaceLeft          Space available at pPayload.  If nPayload>spaceLeft,
  **                      that means content must spill into overflow pages.
  **   *pnSize            Size of the local cell (not counting overflow pages)
  **   pPrior             Where to write the pgno of the first overflow page
  **
  ** Use a call to btreeParseCellPtr() to verify that the values above
  ** were computed correctly.
  */
#ifdef SQLITE_DEBUG
  {
    CellInfo info;
    pPage->xParseCell(pPage, pCell, &info);
    assert( nHeader==(int)(info.pPayload - pCell) );
    assert( info.nKey==pX->nKey );
    assert( *pnSize == info.nSize );
    assert( spaceLeft == info.nLocal );
  }
#endif

  /* Write the payload into the local Cell and any extra into overflow pages */
  while( nPayload>0 ){
    if( spaceLeft==0 ){
#ifndef SQLITE_OMIT_AUTOVACUUM
      Pgno pgnoPtrmap = pgnoOvfl; /* Overflow page pointer-map entry page */
      if( pBt->autoVacuum ){
        do{
          pgnoOvfl++;
        } while(
          PTRMAP_ISPAGE(pBt, pgnoOvfl) || pgnoOvfl==PENDING_BYTE_PAGE(pBt)
        );
      }
#endif
      rc = allocateBtreePage(pBt, &pOvfl, &pgnoOvfl, pgnoOvfl, 0);
#ifndef SQLITE_OMIT_AUTOVACUUM
      /* If the database supports auto-vacuum, and the second or subsequent
      ** overflow page is being allocated, add an entry to the pointer-map
      ** for that page now.
      **
      ** If this is the first overflow page, then write a partial entry
      ** to the pointer-map. If we write nothing to this pointer-map slot,
      ** then the optimistic overflow chain processing in clearCell()
      ** may misinterpret the uninitialized values and delete the
      ** wrong pages from the database.
      */
      if( pBt->autoVacuum && rc==SQLITE_OK ){
        u8 eType = (pgnoPtrmap?PTRMAP_OVERFLOW2:PTRMAP_OVERFLOW1);
        ptrmapPut(pBt, pgnoOvfl, eType, pgnoPtrmap, &rc);
        if( rc ){
          releasePage(pOvfl);
        }
      }
#endif
      if( rc ){
        releasePage(pToRelease);
        return rc;
      }

      /* If pToRelease is not zero than pPrior points into the data area
      ** of pToRelease.  Make sure pToRelease is still writeable. */
      assert( pToRelease==0 || sqlite3PagerIswriteable(pToRelease->pDbPage) );

      /* If pPrior is part of the data area of pPage, then make sure pPage
      ** is still writeable */
      assert( pPrior<pPage->aData || pPrior>=&pPage->aData[pBt->pageSize]
            || sqlite3PagerIswriteable(pPage->pDbPage) );

      put4byte(pPrior, pgnoOvfl);
      releasePage(pToRelease);
      pToRelease = pOvfl;
      pPrior = pOvfl->aData;
      put4byte(pPrior, 0);
      pPayload = &pOvfl->aData[4];
      spaceLeft = pBt->usableSize - 4;
    }
    n = nPayload;
    if( n>spaceLeft ) n = spaceLeft;

    /* If pToRelease is not zero than pPayload points into the data area
    ** of pToRelease.  Make sure pToRelease is still writeable. */
    assert( pToRelease==0 || sqlite3PagerIswriteable(pToRelease->pDbPage) );

    /* If pPayload is part of the data area of pPage, then make sure pPage
    ** is still writeable */
    assert( pPayload<pPage->aData || pPayload>=&pPage->aData[pBt->pageSize]
            || sqlite3PagerIswriteable(pPage->pDbPage) );

    if( nSrc>0 ){
      if( n>nSrc ) n = nSrc;
      assert( pSrc );
      memcpy(pPayload, pSrc, n);
    }else{
      memset(pPayload, 0, n);
    }
    nPayload -= n;
    pPayload += n;
    pSrc += n;
    nSrc -= n;
    spaceLeft -= n;
  }
  releasePage(pToRelease);
  return SQLITE_OK;
}