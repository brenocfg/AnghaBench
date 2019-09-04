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
typedef  int /*<<< orphan*/  uid_t ;
struct stat {int st_mode; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; } ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int SQLITE_IOERR_FSTAT ; 
 int SQLITE_OK ; 
 scalar_t__ osStat (char const*,struct stat*) ; 

__attribute__((used)) static int getFileMode(
  const char *zFile,              /* File name */
  mode_t *pMode,                  /* OUT: Permissions of zFile */
  uid_t *pUid,                    /* OUT: uid of zFile. */
  gid_t *pGid                     /* OUT: gid of zFile. */
){
  struct stat sStat;              /* Output of stat() on database file */
  int rc = SQLITE_OK;
  if( 0==osStat(zFile, &sStat) ){
    *pMode = sStat.st_mode & 0777;
    *pUid = sStat.st_uid;
    *pGid = sStat.st_gid;
  }else{
    rc = SQLITE_IOERR_FSTAT;
  }
  return rc;
}