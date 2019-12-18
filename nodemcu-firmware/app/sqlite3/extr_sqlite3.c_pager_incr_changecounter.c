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
struct TYPE_12__ {scalar_t__ eState; int changeCountDone; scalar_t__ dbSize; scalar_t__ dbFileSize; int /*<<< orphan*/  dbFileVers; int /*<<< orphan*/ * aStat; int /*<<< orphan*/  pageSize; int /*<<< orphan*/  fd; int /*<<< orphan*/  tempFile; } ;
struct TYPE_11__ {int /*<<< orphan*/  pData; } ;
typedef  TYPE_1__ PgHdr ;
typedef  TYPE_2__ Pager ;

/* Variables and functions */
 scalar_t__ ALWAYS (int) ; 
 int /*<<< orphan*/  CODEC2 (TYPE_2__*,int /*<<< orphan*/ ,int,int,int,void const*) ; 
 scalar_t__ DIRECT_MODE ; 
 size_t PAGER_STAT_WRITE ; 
 scalar_t__ PAGER_WRITER_CACHEMOD ; 
 scalar_t__ PAGER_WRITER_DBMOD ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int assert_pager_state (TYPE_2__*) ; 
 scalar_t__ isOpen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int) ; 
 int /*<<< orphan*/  pager_write_changecounter (TYPE_1__*) ; 
 int sqlite3OsWrite (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3PagerGet (TYPE_2__*,int,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3PagerUnref (TYPE_1__*) ; 
 int sqlite3PagerWrite (TYPE_1__*) ; 

__attribute__((used)) static int pager_incr_changecounter(Pager *pPager, int isDirectMode){
  int rc = SQLITE_OK;

  assert( pPager->eState==PAGER_WRITER_CACHEMOD
       || pPager->eState==PAGER_WRITER_DBMOD
  );
  assert( assert_pager_state(pPager) );

  /* Declare and initialize constant integer 'isDirect'. If the
  ** atomic-write optimization is enabled in this build, then isDirect
  ** is initialized to the value passed as the isDirectMode parameter
  ** to this function. Otherwise, it is always set to zero.
  **
  ** The idea is that if the atomic-write optimization is not
  ** enabled at compile time, the compiler can omit the tests of
  ** 'isDirect' below, as well as the block enclosed in the
  ** "if( isDirect )" condition.
  */
#ifndef SQLITE_ENABLE_ATOMIC_WRITE
# define DIRECT_MODE 0
  assert( isDirectMode==0 );
  UNUSED_PARAMETER(isDirectMode);
#else
# define DIRECT_MODE isDirectMode
#endif

  if( !pPager->changeCountDone && ALWAYS(pPager->dbSize>0) ){
    PgHdr *pPgHdr;                /* Reference to page 1 */

    assert( !pPager->tempFile && isOpen(pPager->fd) );

    /* Open page 1 of the file for writing. */
    rc = sqlite3PagerGet(pPager, 1, &pPgHdr, 0);
    assert( pPgHdr==0 || rc==SQLITE_OK );

    /* If page one was fetched successfully, and this function is not
    ** operating in direct-mode, make page 1 writable.  When not in
    ** direct mode, page 1 is always held in cache and hence the PagerGet()
    ** above is always successful - hence the ALWAYS on rc==SQLITE_OK.
    */
    if( !DIRECT_MODE && ALWAYS(rc==SQLITE_OK) ){
      rc = sqlite3PagerWrite(pPgHdr);
    }

    if( rc==SQLITE_OK ){
      /* Actually do the update of the change counter */
      pager_write_changecounter(pPgHdr);

      /* If running in direct mode, write the contents of page 1 to the file. */
      if( DIRECT_MODE ){
        const void *zBuf;
        assert( pPager->dbFileSize>0 );
        CODEC2(pPager, pPgHdr->pData, 1, 6, rc=SQLITE_NOMEM_BKPT, zBuf);
        if( rc==SQLITE_OK ){
          rc = sqlite3OsWrite(pPager->fd, zBuf, pPager->pageSize, 0);
          pPager->aStat[PAGER_STAT_WRITE]++;
        }
        if( rc==SQLITE_OK ){
          /* Update the pager's copy of the change-counter. Otherwise, the
          ** next time a read transaction is opened the cache will be
          ** flushed (as the change-counter values will not match).  */
          const void *pCopy = (const void *)&((const char *)zBuf)[24];
          memcpy(&pPager->dbFileVers, pCopy, sizeof(pPager->dbFileVers));
          pPager->changeCountDone = 1;
        }
      }else{
        pPager->changeCountDone = 1;
      }
    }

    /* Release the page reference. */
    sqlite3PagerUnref(pPgHdr);
  }
  return rc;
}