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
#define  EACCES 134 
#define  EAGAIN 133 
#define  EBUSY 132 
#define  EINTR 131 
#define  ENOLCK 130 
#define  EPERM 129 
#define  ETIMEDOUT 128 
 int SQLITE_BUSY ; 
 int SQLITE_IOERR_CHECKRESERVEDLOCK ; 
 int SQLITE_IOERR_LOCK ; 
 int SQLITE_IOERR_RDLOCK ; 
 int SQLITE_IOERR_UNLOCK ; 
 int SQLITE_PERM ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int sqliteErrorFromPosixError(int posixError, int sqliteIOErr) {
  assert( (sqliteIOErr == SQLITE_IOERR_LOCK) || 
          (sqliteIOErr == SQLITE_IOERR_UNLOCK) || 
          (sqliteIOErr == SQLITE_IOERR_RDLOCK) ||
          (sqliteIOErr == SQLITE_IOERR_CHECKRESERVEDLOCK) );
  switch (posixError) {
  case EACCES: 
  case EAGAIN:
  case ETIMEDOUT:
  case EBUSY:
  case EINTR:
  case ENOLCK:  
    /* random NFS retry error, unless during file system support 
     * introspection, in which it actually means what it says */
    return SQLITE_BUSY;
    
  case EPERM: 
    return SQLITE_PERM;
    
  default: 
    return sqliteIOErr;
  }
}