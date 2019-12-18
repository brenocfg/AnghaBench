#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int eFileLock; int lastErrno; int szChunk; int iBusyTimeout; int mmapSizeMax; int /*<<< orphan*/  dbUpdate; int /*<<< orphan*/  mmapSize; int /*<<< orphan*/  nFetchOut; TYPE_1__* pVfs; int /*<<< orphan*/  h; } ;
typedef  TYPE_2__ unixFile ;
typedef  int /*<<< orphan*/  sqlite3_file ;
typedef  int i64 ;
struct TYPE_11__ {int mxMmap; } ;
struct TYPE_9__ {int /*<<< orphan*/  mxPathname; int /*<<< orphan*/  zName; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_IOC_ABORT_VOLATILE_WRITE ; 
 int /*<<< orphan*/  F2FS_IOC_COMMIT_ATOMIC_WRITE ; 
 int /*<<< orphan*/  F2FS_IOC_START_ATOMIC_WRITE ; 
#define  SQLITE_FCNTL_BEGIN_ATOMIC_WRITE 144 
#define  SQLITE_FCNTL_CHUNK_SIZE 143 
#define  SQLITE_FCNTL_COMMIT_ATOMIC_WRITE 142 
#define  SQLITE_FCNTL_DB_UNCHANGED 141 
#define  SQLITE_FCNTL_GET_LOCKPROXYFILE 140 
#define  SQLITE_FCNTL_HAS_MOVED 139 
#define  SQLITE_FCNTL_LAST_ERRNO 138 
#define  SQLITE_FCNTL_LOCKSTATE 137 
#define  SQLITE_FCNTL_LOCK_TIMEOUT 136 
#define  SQLITE_FCNTL_MMAP_SIZE 135 
#define  SQLITE_FCNTL_PERSIST_WAL 134 
#define  SQLITE_FCNTL_POWERSAFE_OVERWRITE 133 
#define  SQLITE_FCNTL_ROLLBACK_ATOMIC_WRITE 132 
#define  SQLITE_FCNTL_SET_LOCKPROXYFILE 131 
#define  SQLITE_FCNTL_SIZE_HINT 130 
#define  SQLITE_FCNTL_TEMPFILENAME 129 
#define  SQLITE_FCNTL_VFSNAME 128 
 int SQLITE_IOERR_BEGIN_ATOMIC ; 
 int SQLITE_IOERR_COMMIT_ATOMIC ; 
 int SQLITE_IOERR_ROLLBACK_ATOMIC ; 
 int SQLITE_NOTFOUND ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SimulateIOErrorBenign (int) ; 
 int /*<<< orphan*/  UNIXFILE_PERSIST_WAL ; 
 int /*<<< orphan*/  UNIXFILE_PSOW ; 
 int fcntlSizeHint (TYPE_2__*,int) ; 
 int fileHasMoved (TYPE_2__*) ; 
 int osIoctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int proxyFileControl (int /*<<< orphan*/ *,int,void*) ; 
 TYPE_6__ sqlite3GlobalConfig ; 
 char* sqlite3_malloc64 (int /*<<< orphan*/ ) ; 
 char* sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unixGetTempname (int /*<<< orphan*/ ,char*) ; 
 int unixMapfile (TYPE_2__*,int) ; 
 int /*<<< orphan*/  unixModeBit (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  unixUnmapfile (TYPE_2__*) ; 

__attribute__((used)) static int unixFileControl(sqlite3_file *id, int op, void *pArg){
  unixFile *pFile = (unixFile*)id;
  switch( op ){
#if defined(__linux__) && defined(SQLITE_ENABLE_BATCH_ATOMIC_WRITE)
    case SQLITE_FCNTL_BEGIN_ATOMIC_WRITE: {
      int rc = osIoctl(pFile->h, F2FS_IOC_START_ATOMIC_WRITE);
      return rc ? SQLITE_IOERR_BEGIN_ATOMIC : SQLITE_OK;
    }
    case SQLITE_FCNTL_COMMIT_ATOMIC_WRITE: {
      int rc = osIoctl(pFile->h, F2FS_IOC_COMMIT_ATOMIC_WRITE);
      return rc ? SQLITE_IOERR_COMMIT_ATOMIC : SQLITE_OK;
    }
    case SQLITE_FCNTL_ROLLBACK_ATOMIC_WRITE: {
      int rc = osIoctl(pFile->h, F2FS_IOC_ABORT_VOLATILE_WRITE);
      return rc ? SQLITE_IOERR_ROLLBACK_ATOMIC : SQLITE_OK;
    }
#endif /* __linux__ && SQLITE_ENABLE_BATCH_ATOMIC_WRITE */

    case SQLITE_FCNTL_LOCKSTATE: {
      *(int*)pArg = pFile->eFileLock;
      return SQLITE_OK;
    }
    case SQLITE_FCNTL_LAST_ERRNO: {
      *(int*)pArg = pFile->lastErrno;
      return SQLITE_OK;
    }
    case SQLITE_FCNTL_CHUNK_SIZE: {
      pFile->szChunk = *(int *)pArg;
      return SQLITE_OK;
    }
    case SQLITE_FCNTL_SIZE_HINT: {
      int rc;
      SimulateIOErrorBenign(1);
      rc = fcntlSizeHint(pFile, *(i64 *)pArg);
      SimulateIOErrorBenign(0);
      return rc;
    }
    case SQLITE_FCNTL_PERSIST_WAL: {
      unixModeBit(pFile, UNIXFILE_PERSIST_WAL, (int*)pArg);
      return SQLITE_OK;
    }
    case SQLITE_FCNTL_POWERSAFE_OVERWRITE: {
      unixModeBit(pFile, UNIXFILE_PSOW, (int*)pArg);
      return SQLITE_OK;
    }
    case SQLITE_FCNTL_VFSNAME: {
      *(char**)pArg = sqlite3_mprintf("%s", pFile->pVfs->zName);
      return SQLITE_OK;
    }
    case SQLITE_FCNTL_TEMPFILENAME: {
      char *zTFile = sqlite3_malloc64( pFile->pVfs->mxPathname );
      if( zTFile ){
        unixGetTempname(pFile->pVfs->mxPathname, zTFile);
        *(char**)pArg = zTFile;
      }
      return SQLITE_OK;
    }
    case SQLITE_FCNTL_HAS_MOVED: {
      *(int*)pArg = fileHasMoved(pFile);
      return SQLITE_OK;
    }
#ifdef SQLITE_ENABLE_SETLK_TIMEOUT
    case SQLITE_FCNTL_LOCK_TIMEOUT: {
      pFile->iBusyTimeout = *(int*)pArg;
      return SQLITE_OK;
    }
#endif
#if SQLITE_MAX_MMAP_SIZE>0
    case SQLITE_FCNTL_MMAP_SIZE: {
      i64 newLimit = *(i64*)pArg;
      int rc = SQLITE_OK;
      if( newLimit>sqlite3GlobalConfig.mxMmap ){
        newLimit = sqlite3GlobalConfig.mxMmap;
      }

      /* The value of newLimit may be eventually cast to (size_t) and passed
      ** to mmap(). Restrict its value to 2GB if (size_t) is not at least a
      ** 64-bit type. */
      if( newLimit>0 && sizeof(size_t)<8 ){
        newLimit = (newLimit & 0x7FFFFFFF);
      }

      *(i64*)pArg = pFile->mmapSizeMax;
      if( newLimit>=0 && newLimit!=pFile->mmapSizeMax && pFile->nFetchOut==0 ){
        pFile->mmapSizeMax = newLimit;
        if( pFile->mmapSize>0 ){
          unixUnmapfile(pFile);
          rc = unixMapfile(pFile, -1);
        }
      }
      return rc;
    }
#endif
#ifdef SQLITE_DEBUG
    /* The pager calls this method to signal that it has done
    ** a rollback and that the database is therefore unchanged and
    ** it hence it is OK for the transaction change counter to be
    ** unchanged.
    */
    case SQLITE_FCNTL_DB_UNCHANGED: {
      ((unixFile*)id)->dbUpdate = 0;
      return SQLITE_OK;
    }
#endif
#if SQLITE_ENABLE_LOCKING_STYLE && defined(__APPLE__)
    case SQLITE_FCNTL_SET_LOCKPROXYFILE:
    case SQLITE_FCNTL_GET_LOCKPROXYFILE: {
      return proxyFileControl(id,op,pArg);
    }
#endif /* SQLITE_ENABLE_LOCKING_STYLE && defined(__APPLE__) */
  }
  return SQLITE_NOTFOUND;
}