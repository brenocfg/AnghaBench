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
struct TYPE_3__ {scalar_t__ dbSize; int /*<<< orphan*/  fd; scalar_t__* zFilename; scalar_t__ tempFile; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_FCNTL_HAS_MOVED ; 
 int SQLITE_NOTFOUND ; 
 int SQLITE_OK ; 
 int SQLITE_READONLY_DBMOVED ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3OsFileControl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int databaseIsUnmoved(Pager *pPager){
  int bHasMoved = 0;
  int rc;

  if( pPager->tempFile ) return SQLITE_OK;
  if( pPager->dbSize==0 ) return SQLITE_OK;
  assert( pPager->zFilename && pPager->zFilename[0] );
  rc = sqlite3OsFileControl(pPager->fd, SQLITE_FCNTL_HAS_MOVED, &bHasMoved);
  if( rc==SQLITE_NOTFOUND ){
    /* If the HAS_MOVED file-control is unimplemented, assume that the file
    ** has not been moved.  That is the historical behavior of SQLite: prior to
    ** version 3.8.3, it never checked */
    rc = SQLITE_OK;
  }else if( rc==SQLITE_OK && bHasMoved ){
    rc = SQLITE_READONLY_DBMOVED;
  }
  return rc;
}