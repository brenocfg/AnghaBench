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
struct TYPE_3__ {scalar_t__ nRef; scalar_t__ h; int exclMask; int sharedMask; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_1__ unixShmNode ;
typedef  int u16 ;
struct flock {int l_type; int l_start; int l_len; int /*<<< orphan*/  l_whence; } ;
typedef  int /*<<< orphan*/  f ;

/* Variables and functions */
 int F_RDLCK ; 
 int /*<<< orphan*/  F_SETLK ; 
 int F_UNLCK ; 
 int F_WRLCK ; 
 int /*<<< orphan*/  OSTRACE (char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SQLITE_BUSY ; 
 int SQLITE_OK ; 
 int SQLITE_SHM_NLOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (struct flock*,int /*<<< orphan*/ ,int) ; 
 int osFcntl (scalar_t__,int /*<<< orphan*/ ,struct flock*) ; 
 scalar_t__ sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unixShmSystemLock(
  unixShmNode *pShmNode, /* Apply locks to this open shared-memory segment */
  int lockType,          /* F_UNLCK, F_RDLCK, or F_WRLCK */
  int ofst,              /* First byte of the locking range */
  int n                  /* Number of bytes to lock */
){
  struct flock f;       /* The posix advisory locking structure */
  int rc = SQLITE_OK;   /* Result code form fcntl() */

  /* Access to the unixShmNode object is serialized by the caller */
  assert( sqlite3_mutex_held(pShmNode->mutex) || pShmNode->nRef==0 );

  /* Shared locks never span more than one byte */
  assert( n==1 || lockType!=F_RDLCK );

  /* Locks are within range */
  assert( n>=1 && n<SQLITE_SHM_NLOCK );

  if( pShmNode->h>=0 ){
    /* Initialize the locking parameters */
    memset(&f, 0, sizeof(f));
    f.l_type = lockType;
    f.l_whence = SEEK_SET;
    f.l_start = ofst;
    f.l_len = n;

    rc = osFcntl(pShmNode->h, F_SETLK, &f);
    rc = (rc!=(-1)) ? SQLITE_OK : SQLITE_BUSY;
  }

  /* Update the global lock state and do debug tracing */
#ifdef SQLITE_DEBUG
  { u16 mask;
  OSTRACE(("SHM-LOCK "));
  mask = (1<<(ofst+n)) - (1<<ofst);
  if( rc==SQLITE_OK ){
    if( lockType==F_UNLCK ){
      OSTRACE(("unlock %d ok", ofst));
      pShmNode->exclMask &= ~mask;
      pShmNode->sharedMask &= ~mask;
    }else if( lockType==F_RDLCK ){
      OSTRACE(("read-lock %d ok", ofst));
      pShmNode->exclMask &= ~mask;
      pShmNode->sharedMask |= mask;
    }else{
      assert( lockType==F_WRLCK );
      OSTRACE(("write-lock %d ok", ofst));
      pShmNode->exclMask |= mask;
      pShmNode->sharedMask &= ~mask;
    }
  }else{
    if( lockType==F_UNLCK ){
      OSTRACE(("unlock %d failed", ofst));
    }else if( lockType==F_RDLCK ){
      OSTRACE(("read-lock failed"));
    }else{
      assert( lockType==F_WRLCK );
      OSTRACE(("write-lock %d failed", ofst));
    }
  }
  OSTRACE((" - afterwards %03x,%03x\n",
           pShmNode->sharedMask, pShmNode->exclMask));
  }
#endif

  return rc;        
}