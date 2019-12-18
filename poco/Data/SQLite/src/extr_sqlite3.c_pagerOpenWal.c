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
struct TYPE_5__ {scalar_t__ pWal; scalar_t__ tempFile; scalar_t__ eLock; int /*<<< orphan*/  journalSizeLimit; scalar_t__ exclusiveMode; int /*<<< orphan*/  zWal; int /*<<< orphan*/  fd; int /*<<< orphan*/  pVfs; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ EXCLUSIVE_LOCK ; 
 scalar_t__ SHARED_LOCK ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int pagerExclusiveLock (TYPE_1__*) ; 
 int /*<<< orphan*/  pagerFixMaplimit (TYPE_1__*) ; 
 int sqlite3WalOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int pagerOpenWal(Pager *pPager){
  int rc = SQLITE_OK;

  assert( pPager->pWal==0 && pPager->tempFile==0 );
  assert( pPager->eLock==SHARED_LOCK || pPager->eLock==EXCLUSIVE_LOCK );

  /* If the pager is already in exclusive-mode, the WAL module will use 
  ** heap-memory for the wal-index instead of the VFS shared-memory 
  ** implementation. Take the exclusive lock now, before opening the WAL
  ** file, to make sure this is safe.
  */
  if( pPager->exclusiveMode ){
    rc = pagerExclusiveLock(pPager);
  }

  /* Open the connection to the log file. If this operation fails, 
  ** (e.g. due to malloc() failure), return an error code.
  */
  if( rc==SQLITE_OK ){
    rc = sqlite3WalOpen(pPager->pVfs,
        pPager->fd, pPager->zWal, pPager->exclusiveMode,
        pPager->journalSizeLimit, &pPager->pWal
    );
  }
  pagerFixMaplimit(pPager);

  return rc;
}