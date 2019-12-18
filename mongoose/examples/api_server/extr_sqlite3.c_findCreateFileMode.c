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
typedef  scalar_t__ uid_t ;
struct stat {int st_mode; scalar_t__ st_gid; scalar_t__ st_uid; } ;
typedef  int mode_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_PATHNAME ; 
 int SQLITE_IOERR_FSTAT ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_DELETEONCLOSE ; 
 int SQLITE_OPEN_MAIN_JOURNAL ; 
 int SQLITE_OPEN_WAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ osStat (char*,struct stat*) ; 
 scalar_t__ sqlite3Isalnum (char const) ; 
 int sqlite3Strlen30 (char const*) ; 

__attribute__((used)) static int findCreateFileMode(
  const char *zPath,              /* Path of file (possibly) being created */
  int flags,                      /* Flags passed as 4th argument to xOpen() */
  mode_t *pMode,                  /* OUT: Permissions to open file with */
  uid_t *pUid,                    /* OUT: uid to set on the file */
  gid_t *pGid                     /* OUT: gid to set on the file */
){
  int rc = SQLITE_OK;             /* Return Code */
  *pMode = 0;
  *pUid = 0;
  *pGid = 0;
  if( flags & (SQLITE_OPEN_WAL|SQLITE_OPEN_MAIN_JOURNAL) ){
    char zDb[MAX_PATHNAME+1];     /* Database file path */
    int nDb;                      /* Number of valid bytes in zDb */
    struct stat sStat;            /* Output of stat() on database file */

    /* zPath is a path to a WAL or journal file. The following block derives
    ** the path to the associated database file from zPath. This block handles
    ** the following naming conventions:
    **
    **   "<path to db>-journal"
    **   "<path to db>-wal"
    **   "<path to db>-journalNN"
    **   "<path to db>-walNN"
    **
    ** where NN is a decimal number. The NN naming schemes are 
    ** used by the test_multiplex.c module.
    */
    nDb = sqlite3Strlen30(zPath) - 1; 
#ifdef SQLITE_ENABLE_8_3_NAMES
    while( nDb>0 && sqlite3Isalnum(zPath[nDb]) ) nDb--;
    if( nDb==0 || zPath[nDb]!='-' ) return SQLITE_OK;
#else
    while( zPath[nDb]!='-' ){
      assert( nDb>0 );
      assert( zPath[nDb]!='\n' );
      nDb--;
    }
#endif
    memcpy(zDb, zPath, nDb);
    zDb[nDb] = '\0';

    if( 0==osStat(zDb, &sStat) ){
      *pMode = sStat.st_mode & 0777;
      *pUid = sStat.st_uid;
      *pGid = sStat.st_gid;
    }else{
      rc = SQLITE_IOERR_FSTAT;
    }
  }else if( flags & SQLITE_OPEN_DELETEONCLOSE ){
    *pMode = 0600;
  }
  return rc;
}