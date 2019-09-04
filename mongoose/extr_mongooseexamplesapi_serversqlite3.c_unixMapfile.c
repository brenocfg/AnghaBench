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
typedef  int /*<<< orphan*/  unixFile ;
typedef  int /*<<< orphan*/  i64 ;

/* Variables and functions */
 int SQLITE_OK ; 

__attribute__((used)) static int unixMapfile(unixFile *pFd, i64 nByte){
#if SQLITE_MAX_MMAP_SIZE>0
  i64 nMap = nByte;
  int rc;

  assert( nMap>=0 || pFd->nFetchOut==0 );
  if( pFd->nFetchOut>0 ) return SQLITE_OK;

  if( nMap<0 ){
    struct stat statbuf;          /* Low-level file information */
    rc = osFstat(pFd->h, &statbuf);
    if( rc!=SQLITE_OK ){
      return SQLITE_IOERR_FSTAT;
    }
    nMap = statbuf.st_size;
  }
  if( nMap>pFd->mmapSizeMax ){
    nMap = pFd->mmapSizeMax;
  }

  if( nMap!=pFd->mmapSize ){
    if( nMap>0 ){
      unixRemapfile(pFd, nMap);
    }else{
      unixUnmapfile(pFd);
    }
  }
#endif

  return SQLITE_OK;
}