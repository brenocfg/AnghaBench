#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ eState; int /*<<< orphan*/  fd; int /*<<< orphan*/  pWal; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ PAGER_OPEN ; 
 scalar_t__ PAGER_READER ; 
 int SQLITE_OK ; 
 scalar_t__ USEFETCH (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int pagerUseWal (TYPE_1__*) ; 
 int /*<<< orphan*/  pager_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3OsUnfetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sqlite3WalBeginReadTransaction (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sqlite3WalEndReadTransaction (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pagerBeginReadTransaction(Pager *pPager){
  int rc;                         /* Return code */
  int changed = 0;                /* True if cache must be reset */

  assert( pagerUseWal(pPager) );
  assert( pPager->eState==PAGER_OPEN || pPager->eState==PAGER_READER );

  /* sqlite3WalEndReadTransaction() was not called for the previous
  ** transaction in locking_mode=EXCLUSIVE.  So call it now.  If we
  ** are in locking_mode=NORMAL and EndRead() was previously called,
  ** the duplicate call is harmless.
  */
  sqlite3WalEndReadTransaction(pPager->pWal);

  rc = sqlite3WalBeginReadTransaction(pPager->pWal, &changed);
  if( rc!=SQLITE_OK || changed ){
    pager_reset(pPager);
    if( USEFETCH(pPager) ) sqlite3OsUnfetch(pPager->fd, 0, 0);
  }

  return rc;
}