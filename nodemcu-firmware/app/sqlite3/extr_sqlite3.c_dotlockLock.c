#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int eFileLock; scalar_t__ lockingContext; } ;
typedef  TYPE_1__ unixFile ;
typedef  int /*<<< orphan*/  sqlite3_file ;

/* Variables and functions */
 int EEXIST ; 
 int NO_LOCK ; 
 int SQLITE_BUSY ; 
 int /*<<< orphan*/  SQLITE_IOERR_LOCK ; 
 int SQLITE_OK ; 
 int errno ; 
 int osMkdir (char*,int) ; 
 int sqliteErrorFromPosixError (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storeLastErrno (TYPE_1__*,int) ; 
 int /*<<< orphan*/  utime (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  utimes (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dotlockLock(sqlite3_file *id, int eFileLock) {
  unixFile *pFile = (unixFile*)id;
  char *zLockFile = (char *)pFile->lockingContext;
  int rc = SQLITE_OK;


  /* If we have any lock, then the lock file already exists.  All we have
  ** to do is adjust our internal record of the lock level.
  */
  if( pFile->eFileLock > NO_LOCK ){
    pFile->eFileLock = eFileLock;
    /* Always update the timestamp on the old file */
#ifdef HAVE_UTIME
    utime(zLockFile, NULL);
#else
    utimes(zLockFile, NULL);
#endif
    return SQLITE_OK;
  }

  /* grab an exclusive lock */
  rc = osMkdir(zLockFile, 0777);
  if( rc<0 ){
    /* failed to open/create the lock directory */
    int tErrno = errno;
    if( EEXIST == tErrno ){
      rc = SQLITE_BUSY;
    } else {
      rc = sqliteErrorFromPosixError(tErrno, SQLITE_IOERR_LOCK);
      if( rc!=SQLITE_BUSY ){
        storeLastErrno(pFile, tErrno);
      }
    }
    return rc;
  }

  /* got it, set the type and return ok */
  pFile->eFileLock = eFileLock;
  return rc;
}