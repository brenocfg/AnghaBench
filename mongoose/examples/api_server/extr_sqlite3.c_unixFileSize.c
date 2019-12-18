#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lastErrno; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ unixFile ;
struct stat {int st_size; } ;
typedef  int /*<<< orphan*/  sqlite3_file ;
typedef  int i64 ;

/* Variables and functions */
 int SQLITE_IOERR_FSTAT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SimulateIOError (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int osFstat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int unixFileSize(sqlite3_file *id, i64 *pSize){
  int rc;
  struct stat buf;
  assert( id );
  rc = osFstat(((unixFile*)id)->h, &buf);
  SimulateIOError( rc=1 );
  if( rc!=0 ){
    ((unixFile*)id)->lastErrno = errno;
    return SQLITE_IOERR_FSTAT;
  }
  *pSize = buf.st_size;

  /* When opening a zero-size database, the findInodeInfo() procedure
  ** writes a single byte into that file in order to work around a bug
  ** in the OS-X msdos filesystem.  In order to avoid problems with upper
  ** layers, we need to report this file size as zero even though it is
  ** really 1.   Ticket #3260.
  */
  if( *pSize==1 ) *pSize = 0;


  return SQLITE_OK;
}