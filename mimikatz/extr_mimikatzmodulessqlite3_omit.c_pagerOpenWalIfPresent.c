#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ eState; scalar_t__ eLock; scalar_t__ journalMode; int /*<<< orphan*/  pPCache; int /*<<< orphan*/  zWal; int /*<<< orphan*/  pVfs; int /*<<< orphan*/  tempFile; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ PAGER_JOURNALMODE_DELETE ; 
 scalar_t__ PAGER_JOURNALMODE_WAL ; 
 scalar_t__ PAGER_OPEN ; 
 scalar_t__ SHARED_LOCK ; 
 int /*<<< orphan*/  SQLITE_ACCESS_EXISTS ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int pagerPagecount (TYPE_1__*,scalar_t__*) ; 
 int sqlite3OsAccess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int sqlite3OsDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3PagerOpenWal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3PcachePagecount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static int pagerOpenWalIfPresent(Pager *pPager){
  int rc = SQLITE_OK;
  assert( pPager->eState==PAGER_OPEN );
  assert( pPager->eLock>=SHARED_LOCK );

  if( !pPager->tempFile ){
    int isWal;                    /* True if WAL file exists */
    rc = sqlite3OsAccess(
        pPager->pVfs, pPager->zWal, SQLITE_ACCESS_EXISTS, &isWal
    );
    if( rc==SQLITE_OK ){
      if( isWal ){
        Pgno nPage;                   /* Size of the database file */

        rc = pagerPagecount(pPager, &nPage);
        if( rc ) return rc;
        if( nPage==0 ){
          rc = sqlite3OsDelete(pPager->pVfs, pPager->zWal, 0);
        }else{
          testcase( sqlite3PcachePagecount(pPager->pPCache)==0 );
          rc = sqlite3PagerOpenWal(pPager, 0);
        }
      }else if( pPager->journalMode==PAGER_JOURNALMODE_WAL ){
        pPager->journalMode = PAGER_JOURNALMODE_DELETE;
      }
    }
  }
  return rc;
}