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

/* Variables and functions */
 int /*<<< orphan*/  MAX_PATHNAME ; 
 int /*<<< orphan*/  OSTRACE (char*) ; 
 int O_BINARY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SQLITE_CANTOPEN_BKPT ; 
 int SQLITE_OK ; 
 int robust_open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 scalar_t__ strlen (char*) ; 
 int unixLogError (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int openDirectory(const char *zFilename, int *pFd){
  int ii;
  int fd = -1;
  char zDirname[MAX_PATHNAME+1];

  sqlite3_snprintf(MAX_PATHNAME, zDirname, "%s", zFilename);
  for(ii=(int)strlen(zDirname); ii>0 && zDirname[ii]!='/'; ii--);
  if( ii>0 ){
    zDirname[ii] = '\0';
  }else{
    if( zDirname[0]!='/' ) zDirname[0] = '.';
    zDirname[1] = 0;
  }
  fd = robust_open(zDirname, O_RDONLY|O_BINARY, 0);
  if( fd>=0 ){
    OSTRACE(("OPENDIR %-3d %s\n", fd, zDirname));
  }
  *pFd = fd;
  if( fd>=0 ) return SQLITE_OK;
  return unixLogError(SQLITE_CANTOPEN_BKPT, "openDirectory", zDirname);
}