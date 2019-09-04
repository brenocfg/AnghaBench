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
struct TYPE_4__ {int bProcessLock; scalar_t__ nLock; } ;
typedef  TYPE_1__ unixInodeInfo ;
struct TYPE_5__ {int ctrlFlags; int /*<<< orphan*/  h; TYPE_1__* pInode; } ;
typedef  TYPE_2__ unixFile ;
struct flock {int /*<<< orphan*/  l_type; int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_start; int /*<<< orphan*/  l_whence; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SHARED_FIRST ; 
 int /*<<< orphan*/  SHARED_SIZE ; 
 int UNIXFILE_EXCL ; 
 int UNIXFILE_RDONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int osFcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flock*) ; 
 int unixMutexHeld () ; 

__attribute__((used)) static int unixFileLock(unixFile *pFile, struct flock *pLock){
  int rc;
  unixInodeInfo *pInode = pFile->pInode;
  assert( unixMutexHeld() );
  assert( pInode!=0 );
  if( ((pFile->ctrlFlags & UNIXFILE_EXCL)!=0 || pInode->bProcessLock)
   && ((pFile->ctrlFlags & UNIXFILE_RDONLY)==0)
  ){
    if( pInode->bProcessLock==0 ){
      struct flock lock;
      assert( pInode->nLock==0 );
      lock.l_whence = SEEK_SET;
      lock.l_start = SHARED_FIRST;
      lock.l_len = SHARED_SIZE;
      lock.l_type = F_WRLCK;
      rc = osFcntl(pFile->h, F_SETLK, &lock);
      if( rc<0 ) return rc;
      pInode->bProcessLock = 1;
      pInode->nLock++;
    }else{
      rc = 0;
    }
  }else{
    rc = osFcntl(pFile->h, F_SETLK, pLock);
  }
  return rc;
}