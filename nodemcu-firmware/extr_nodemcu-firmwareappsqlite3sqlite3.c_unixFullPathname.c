#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vfs ;

/* Variables and functions */
 int mkFullPathname (char const*,char*,int) ; 

__attribute__((used)) static int unixFullPathname(
  sqlite3_vfs *pVfs,            /* Pointer to vfs object */
  const char *zPath,            /* Possibly relative input path */
  int nOut,                     /* Size of output buffer in bytes */
  char *zOut                    /* Output buffer */
){
#if !defined(HAVE_READLINK) || !defined(HAVE_LSTAT)
  return mkFullPathname(zPath, zOut, nOut);
#else
  int rc = SQLITE_OK;
  int nByte;
  int nLink = 1;                /* Number of symbolic links followed so far */
  const char *zIn = zPath;      /* Input path for each iteration of loop */
  char *zDel = 0;

  assert( pVfs->mxPathname==MAX_PATHNAME );
  UNUSED_PARAMETER(pVfs);

  /* It's odd to simulate an io-error here, but really this is just
  ** using the io-error infrastructure to test that SQLite handles this
  ** function failing. This function could fail if, for example, the
  ** current working directory has been unlinked.
  */
  SimulateIOError( return SQLITE_ERROR );

  do {

    /* Call stat() on path zIn. Set bLink to true if the path is a symbolic
    ** link, or false otherwise.  */
    int bLink = 0;
    struct stat buf;
    if( osLstat(zIn, &buf)!=0 ){
      if( errno!=ENOENT ){
        rc = unixLogError(SQLITE_CANTOPEN_BKPT, "lstat", zIn);
      }
    }else{
      bLink = S_ISLNK(buf.st_mode);
    }

    if( bLink ){
      if( zDel==0 ){
        zDel = sqlite3_malloc(nOut);
        if( zDel==0 ) rc = SQLITE_NOMEM_BKPT;
      }else if( ++nLink>SQLITE_MAX_SYMLINKS ){
        rc = SQLITE_CANTOPEN_BKPT;
      }

      if( rc==SQLITE_OK ){
        nByte = osReadlink(zIn, zDel, nOut-1);
        if( nByte<0 ){
          rc = unixLogError(SQLITE_CANTOPEN_BKPT, "readlink", zIn);
        }else{
          if( zDel[0]!='/' ){
            int n;
            for(n = sqlite3Strlen30(zIn); n>0 && zIn[n-1]!='/'; n--);
            if( nByte+n+1>nOut ){
              rc = SQLITE_CANTOPEN_BKPT;
            }else{
              memmove(&zDel[n], zDel, nByte+1);
              memcpy(zDel, zIn, n);
              nByte += n;
            }
          }
          zDel[nByte] = '\0';
        }
      }

      zIn = zDel;
    }

    assert( rc!=SQLITE_OK || zIn!=zOut || zIn[0]=='/' );
    if( rc==SQLITE_OK && zIn!=zOut ){
      rc = mkFullPathname(zIn, zOut, nOut);
    }
    if( bLink==0 ) break;
    zIn = zOut;
  }while( rc==SQLITE_OK );

  sqlite3_free(zDel);
  return rc;
#endif   /* HAVE_READLINK && HAVE_LSTAT */
}