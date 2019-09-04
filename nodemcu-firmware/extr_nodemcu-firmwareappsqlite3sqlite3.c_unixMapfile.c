#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ nFetchOut; scalar_t__ mmapSize; scalar_t__ pMapRegion; scalar_t__ mmapSizeMax; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ unixFile ;
struct stat {scalar_t__ st_size; } ;
typedef  scalar_t__ i64 ;

/* Variables and functions */
 int SQLITE_IOERR_FSTAT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ osFstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  unixRemapfile (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int unixMapfile(unixFile *pFd, i64 nMap){
  assert( nMap>=0 || pFd->nFetchOut==0 );
  assert( nMap>0 || (pFd->mmapSize==0 && pFd->pMapRegion==0) );
  if( pFd->nFetchOut>0 ) return SQLITE_OK;

  if( nMap<0 ){
    struct stat statbuf;          /* Low-level file information */
    if( osFstat(pFd->h, &statbuf) ){
      return SQLITE_IOERR_FSTAT;
    }
    nMap = statbuf.st_size;
  }
  if( nMap>pFd->mmapSizeMax ){
    nMap = pFd->mmapSizeMax;
  }

  assert( nMap>0 || (pFd->mmapSize==0 && pFd->pMapRegion==0) );
  if( nMap!=pFd->mmapSize ){
    unixRemapfile(pFd, nMap);
  }

  return SQLITE_OK;
}