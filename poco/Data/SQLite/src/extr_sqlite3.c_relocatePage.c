#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_12__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * pPager; } ;
struct TYPE_11__ {int pgno; int /*<<< orphan*/  pDbPage; int /*<<< orphan*/  aData; TYPE_2__* pBt; } ;
typedef  int Pgno ;
typedef  int /*<<< orphan*/  Pager ;
typedef  TYPE_1__ MemPage ;
typedef  TYPE_2__ BtShared ;

/* Variables and functions */
 int /*<<< orphan*/  PTRMAP_BTREE ; 
 int /*<<< orphan*/  PTRMAP_OVERFLOW1 ; 
 int /*<<< orphan*/  PTRMAP_OVERFLOW2 ; 
 int /*<<< orphan*/  PTRMAP_ROOTPAGE ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int btreeGetPage (TYPE_2__*,int,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int get4byte (int /*<<< orphan*/ ) ; 
 int modifyPagePointer (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptrmapPut (TYPE_2__*,int,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  releasePage (TYPE_1__*) ; 
 int setChildPtrmaps (TYPE_1__*) ; 
 int sqlite3PagerMovepage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int sqlite3PagerWrite (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int relocatePage(
  BtShared *pBt,           /* Btree */
  MemPage *pDbPage,        /* Open page to move */
  u8 eType,                /* Pointer map 'type' entry for pDbPage */
  Pgno iPtrPage,           /* Pointer map 'page-no' entry for pDbPage */
  Pgno iFreePage,          /* The location to move pDbPage to */
  int isCommit             /* isCommit flag passed to sqlite3PagerMovepage */
){
  MemPage *pPtrPage;   /* The page that contains a pointer to pDbPage */
  Pgno iDbPage = pDbPage->pgno;
  Pager *pPager = pBt->pPager;
  int rc;

  assert( eType==PTRMAP_OVERFLOW2 || eType==PTRMAP_OVERFLOW1 || 
      eType==PTRMAP_BTREE || eType==PTRMAP_ROOTPAGE );
  assert( sqlite3_mutex_held(pBt->mutex) );
  assert( pDbPage->pBt==pBt );
  if( iDbPage<3 ) return SQLITE_CORRUPT_BKPT;

  /* Move page iDbPage from its current location to page number iFreePage */
  TRACE(("AUTOVACUUM: Moving %d to free page %d (ptr page %d type %d)\n", 
      iDbPage, iFreePage, iPtrPage, eType));
  rc = sqlite3PagerMovepage(pPager, pDbPage->pDbPage, iFreePage, isCommit);
  if( rc!=SQLITE_OK ){
    return rc;
  }
  pDbPage->pgno = iFreePage;

  /* If pDbPage was a btree-page, then it may have child pages and/or cells
  ** that point to overflow pages. The pointer map entries for all these
  ** pages need to be changed.
  **
  ** If pDbPage is an overflow page, then the first 4 bytes may store a
  ** pointer to a subsequent overflow page. If this is the case, then
  ** the pointer map needs to be updated for the subsequent overflow page.
  */
  if( eType==PTRMAP_BTREE || eType==PTRMAP_ROOTPAGE ){
    rc = setChildPtrmaps(pDbPage);
    if( rc!=SQLITE_OK ){
      return rc;
    }
  }else{
    Pgno nextOvfl = get4byte(pDbPage->aData);
    if( nextOvfl!=0 ){
      ptrmapPut(pBt, nextOvfl, PTRMAP_OVERFLOW2, iFreePage, &rc);
      if( rc!=SQLITE_OK ){
        return rc;
      }
    }
  }

  /* Fix the database pointer on page iPtrPage that pointed at iDbPage so
  ** that it points at iFreePage. Also fix the pointer map entry for
  ** iPtrPage.
  */
  if( eType!=PTRMAP_ROOTPAGE ){
    rc = btreeGetPage(pBt, iPtrPage, &pPtrPage, 0);
    if( rc!=SQLITE_OK ){
      return rc;
    }
    rc = sqlite3PagerWrite(pPtrPage->pDbPage);
    if( rc!=SQLITE_OK ){
      releasePage(pPtrPage);
      return rc;
    }
    rc = modifyPagePointer(pPtrPage, iDbPage, iFreePage, eType);
    releasePage(pPtrPage);
    if( rc==SQLITE_OK ){
      ptrmapPut(pBt, iFreePage, eType, iPtrPage, &rc);
    }
  }
  return rc;
}