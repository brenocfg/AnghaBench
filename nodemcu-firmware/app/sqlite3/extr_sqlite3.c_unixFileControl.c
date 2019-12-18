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
struct TYPE_10__ {int eFileLock; int lastErrno; int szChunk; int /*<<< orphan*/  dbUpdate; int /*<<< orphan*/  mmapSize; int /*<<< orphan*/  mmapSizeMax; int /*<<< orphan*/  nFetchOut; TYPE_1__* pVfs; } ;
typedef  TYPE_2__ unixFile ;
typedef  int /*<<< orphan*/  sqlite3_file ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_11__ {int /*<<< orphan*/  mxMmap; } ;
struct TYPE_9__ {int /*<<< orphan*/  mxPathname; int /*<<< orphan*/  zName; } ;

/* Variables and functions */
#define  SQLITE_FCNTL_CHUNK_SIZE 140 
#define  SQLITE_FCNTL_DB_UNCHANGED 139 
#define  SQLITE_FCNTL_GET_LOCKPROXYFILE 138 
#define  SQLITE_FCNTL_HAS_MOVED 137 
#define  SQLITE_FCNTL_LAST_ERRNO 136 
#define  SQLITE_FCNTL_LOCKSTATE 135 
#define  SQLITE_FCNTL_MMAP_SIZE 134 
#define  SQLITE_FCNTL_PERSIST_WAL 133 
#define  SQLITE_FCNTL_POWERSAFE_OVERWRITE 132 
#define  SQLITE_FCNTL_SET_LOCKPROXYFILE 131 
#define  SQLITE_FCNTL_SIZE_HINT 130 
#define  SQLITE_FCNTL_TEMPFILENAME 129 
#define  SQLITE_FCNTL_VFSNAME 128 
 int SQLITE_NOTFOUND ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SimulateIOErrorBenign (int) ; 
 int /*<<< orphan*/  UNIXFILE_PERSIST_WAL ; 
 int /*<<< orphan*/  UNIXFILE_PSOW ; 
 int fcntlSizeHint (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int fileHasMoved (TYPE_2__*) ; 
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
#if SQLITE_MAX_MMAP_SIZE>0
    case SQLITE_FCNTL_MMAP_SIZE: {
      i64 newLimit = *(i64*)pArg;
      int rc = SQLITE_OK;
      if( newLimit>sqlite3GlobalConfig.mxMmap ){
        newLimit = sqlite3GlobalConfig.mxMmap;
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