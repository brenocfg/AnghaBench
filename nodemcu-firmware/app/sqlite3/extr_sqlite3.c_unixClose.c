#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_5__* pInode; } ;
typedef  TYPE_1__ unixFile ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_7__ {scalar_t__ nLock; scalar_t__ bProcessLock; } ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_5__*) ; 
 int /*<<< orphan*/  NO_LOCK ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int closeUnixFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  releaseInodeInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  setPendingFd (TYPE_1__*) ; 
 int /*<<< orphan*/  unixEnterMutex () ; 
 int /*<<< orphan*/  unixLeaveMutex () ; 
 int /*<<< orphan*/  unixUnlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verifyDbFile (TYPE_1__*) ; 

__attribute__((used)) static int unixClose(sqlite3_file *id){
  int rc = SQLITE_OK;
  unixFile *pFile = (unixFile *)id;
  verifyDbFile(pFile);
  unixUnlock(id, NO_LOCK);
  unixEnterMutex();

  /* unixFile.pInode is always valid here. Otherwise, a different close
  ** routine (e.g. nolockClose()) would be called instead.
  */
  assert( pFile->pInode->nLock>0 || pFile->pInode->bProcessLock==0 );
  if( ALWAYS(pFile->pInode) && pFile->pInode->nLock ){
    /* If there are outstanding locks, do not actually close the file just
    ** yet because that would clear those locks.  Instead, add the file
    ** descriptor to pInode->pUnused list.  It will be automatically closed
    ** when the last lock is cleared.
    */
    setPendingFd(pFile);
  }
  releaseInodeInfo(pFile);
  rc = closeUnixFile(id);
  unixLeaveMutex();
  return rc;
}