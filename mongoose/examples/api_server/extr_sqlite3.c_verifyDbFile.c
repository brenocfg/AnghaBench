#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int ctrlFlags; int /*<<< orphan*/  zPath; TYPE_2__* pInode; int /*<<< orphan*/  h; } ;
typedef  TYPE_3__ unixFile ;
struct stat {int st_nlink; scalar_t__ st_ino; } ;
struct TYPE_5__ {scalar_t__ ino; } ;
struct TYPE_6__ {TYPE_1__ fileId; } ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_WARNING ; 
 int UNIXFILE_DELETE ; 
 int UNIXFILE_WARNED ; 
 int osFstat (int /*<<< orphan*/ ,struct stat*) ; 
 int osStat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  sqlite3_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void verifyDbFile(unixFile *pFile){
  struct stat buf;
  int rc;
  if( pFile->ctrlFlags & UNIXFILE_WARNED ){
    /* One or more of the following warnings have already been issued.  Do not
    ** repeat them so as not to clutter the error log */
    return;
  }
  rc = osFstat(pFile->h, &buf);
  if( rc!=0 ){
    sqlite3_log(SQLITE_WARNING, "cannot fstat db file %s", pFile->zPath);
    pFile->ctrlFlags |= UNIXFILE_WARNED;
    return;
  }
  if( buf.st_nlink==0 && (pFile->ctrlFlags & UNIXFILE_DELETE)==0 ){
    sqlite3_log(SQLITE_WARNING, "file unlinked while open: %s", pFile->zPath);
    pFile->ctrlFlags |= UNIXFILE_WARNED;
    return;
  }
  if( buf.st_nlink>1 ){
    sqlite3_log(SQLITE_WARNING, "multiple links to file: %s", pFile->zPath);
    pFile->ctrlFlags |= UNIXFILE_WARNED;
    return;
  }
  if( pFile->pInode!=0
   && ((rc = osStat(pFile->zPath, &buf))!=0
       || buf.st_ino!=pFile->pInode->fileId.ino)
  ){
    sqlite3_log(SQLITE_WARNING, "file renamed while open: %s", pFile->zPath);
    pFile->ctrlFlags |= UNIXFILE_WARNED;
    return;
  }
}