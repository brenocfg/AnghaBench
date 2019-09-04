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
typedef  int time_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  sqlite3_vfs ;
typedef  int /*<<< orphan*/  pid ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int getpid () ; 
 int /*<<< orphan*/  memcpy (char*,int*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int osRead (int,char*,int) ; 
 int /*<<< orphan*/  robust_close (int /*<<< orphan*/ ,int,int) ; 
 int robust_open (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int*) ; 

__attribute__((used)) static int unixRandomness(sqlite3_vfs *NotUsed, int nBuf, char *zBuf){
  UNUSED_PARAMETER(NotUsed);
  assert((size_t)nBuf>=(sizeof(time_t)+sizeof(int)));

  /* We have to initialize zBuf to prevent valgrind from reporting
  ** errors.  The reports issued by valgrind are incorrect - we would
  ** prefer that the randomness be increased by making use of the
  ** uninitialized space in zBuf - but valgrind errors tend to worry
  ** some users.  Rather than argue, it seems easier just to initialize
  ** the whole array and silence valgrind, even if that means less randomness
  ** in the random seed.
  **
  ** When testing, initializing zBuf[] to zero is all we do.  That means
  ** that we always use the same random number sequence.  This makes the
  ** tests repeatable.
  */
  memset(zBuf, 0, nBuf);
#if !defined(SQLITE_TEST)
  {
    int pid, fd, got;
    fd = robust_open("/dev/urandom", O_RDONLY, 0);
    if( fd<0 ){
      time_t t;
      time(&t);
      memcpy(zBuf, &t, sizeof(t));
      pid = getpid();
      memcpy(&zBuf[sizeof(t)], &pid, sizeof(pid));
      assert( sizeof(t)+sizeof(pid)<=(size_t)nBuf );
      nBuf = sizeof(t) + sizeof(pid);
    }else{
      do{ got = osRead(fd, zBuf, nBuf); }while( got<0 && errno==EINTR );
      robust_close(0, fd, __LINE__);
    }
  }
#endif
  return nBuf;
}