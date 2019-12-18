#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ autoVacuum; TYPE_13__* pCursor; } ;
struct TYPE_16__ {scalar_t__ inTrans; int /*<<< orphan*/  db; TYPE_3__* pBt; } ;
struct TYPE_15__ {int /*<<< orphan*/  db; } ;
struct TYPE_14__ {TYPE_1__* pBtree; } ;
typedef  int Pgno ;
typedef  int /*<<< orphan*/  MemPage ;
typedef  TYPE_2__ Btree ;
typedef  TYPE_3__ BtShared ;

/* Variables and functions */
 int /*<<< orphan*/  BTREE_LARGEST_ROOT_PAGE ; 
 scalar_t__ NEVER (TYPE_13__*) ; 
 int PENDING_BYTE_PAGE (TYPE_3__*) ; 
 int PTF_INTKEY ; 
 int PTF_LEAF ; 
 scalar_t__ PTRMAP_ISPAGE (TYPE_3__*,int) ; 
 int /*<<< orphan*/  PTRMAP_ROOTPAGE ; 
 int SQLITE_LOCKED_SHAREDCACHE ; 
 int SQLITE_OK ; 
 scalar_t__ TRANS_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int btreeGetPage (TYPE_3__*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freePage (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  releasePage (int /*<<< orphan*/ *) ; 
 int relocatePage (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int sqlite3BtreeClearTable (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3BtreeGetMeta (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int sqlite3BtreeHoldsMutex (TYPE_2__*) ; 
 int sqlite3BtreeUpdateMeta (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  sqlite3ConnectionBlocked (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zeroPage (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int btreeDropTable(Btree *p, Pgno iTable, int *piMoved){
  int rc;
  MemPage *pPage = 0;
  BtShared *pBt = p->pBt;

  assert( sqlite3BtreeHoldsMutex(p) );
  assert( p->inTrans==TRANS_WRITE );

  /* It is illegal to drop a table if any cursors are open on the
  ** database. This is because in auto-vacuum mode the backend may
  ** need to move another root-page to fill a gap left by the deleted
  ** root page. If an open cursor was using this page a problem would 
  ** occur.
  **
  ** This error is caught long before control reaches this point.
  */
  if( NEVER(pBt->pCursor) ){
    sqlite3ConnectionBlocked(p->db, pBt->pCursor->pBtree->db);
    return SQLITE_LOCKED_SHAREDCACHE;
  }

  rc = btreeGetPage(pBt, (Pgno)iTable, &pPage, 0, 0);
  if( rc ) return rc;
  rc = sqlite3BtreeClearTable(p, iTable, 0);
  if( rc ){
    releasePage(pPage);
    return rc;
  }

  *piMoved = 0;

  if( iTable>1 ){
#ifdef SQLITE_OMIT_AUTOVACUUM
    freePage(pPage, &rc);
    releasePage(pPage);
#else
    if( pBt->autoVacuum ){
      Pgno maxRootPgno;
      sqlite3BtreeGetMeta(p, BTREE_LARGEST_ROOT_PAGE, &maxRootPgno);

      if( iTable==maxRootPgno ){
        /* If the table being dropped is the table with the largest root-page
        ** number in the database, put the root page on the free list. 
        */
        freePage(pPage, &rc);
        releasePage(pPage);
        if( rc!=SQLITE_OK ){
          return rc;
        }
      }else{
        /* The table being dropped does not have the largest root-page
        ** number in the database. So move the page that does into the 
        ** gap left by the deleted root-page.
        */
        MemPage *pMove;
        releasePage(pPage);
        rc = btreeGetPage(pBt, maxRootPgno, &pMove, 0, 0);
        if( rc!=SQLITE_OK ){
          return rc;
        }
        rc = relocatePage(pBt, pMove, PTRMAP_ROOTPAGE, 0, iTable, 0);
        releasePage(pMove);
        if( rc!=SQLITE_OK ){
          return rc;
        }
        pMove = 0;
        rc = btreeGetPage(pBt, maxRootPgno, &pMove, 0, 0);
        freePage(pMove, &rc);
        releasePage(pMove);
        if( rc!=SQLITE_OK ){
          return rc;
        }
        *piMoved = maxRootPgno;
      }

      /* Set the new 'max-root-page' value in the database header. This
      ** is the old value less one, less one more if that happens to
      ** be a root-page number, less one again if that is the
      ** PENDING_BYTE_PAGE.
      */
      maxRootPgno--;
      while( maxRootPgno==PENDING_BYTE_PAGE(pBt)
             || PTRMAP_ISPAGE(pBt, maxRootPgno) ){
        maxRootPgno--;
      }
      assert( maxRootPgno!=PENDING_BYTE_PAGE(pBt) );

      rc = sqlite3BtreeUpdateMeta(p, 4, maxRootPgno);
    }else{
      freePage(pPage, &rc);
      releasePage(pPage);
    }
#endif
  }else{
    /* If sqlite3BtreeDropTable was called on page 1.
    ** This really never should happen except in a corrupt
    ** database. 
    */
    zeroPage(pPage, PTF_INTKEY|PTF_LEAF );
    releasePage(pPage);
  }
  return rc;  
}