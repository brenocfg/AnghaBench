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
struct TYPE_3__ {int /*<<< orphan*/  h; scalar_t__ lastErrno; } ;
typedef  TYPE_1__ unixFile ;
typedef  int sqlite3_int64 ;
typedef  int i64 ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  OSTRACE (char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SimulateIOError (int) ; 
 int /*<<< orphan*/  TIMER_ELAPSED ; 
 int /*<<< orphan*/  TIMER_END ; 
 int /*<<< orphan*/  TIMER_START ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int osPread (int /*<<< orphan*/ ,void*,int,int) ; 
 int osPread64 (int /*<<< orphan*/ ,void*,int,int) ; 
 int osRead (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int seekAndRead(unixFile *id, sqlite3_int64 offset, void *pBuf, int cnt){
  int got;
  int prior = 0;
#if (!defined(USE_PREAD) && !defined(USE_PREAD64))
  i64 newOffset;
#endif
  TIMER_START;
  assert( cnt==(cnt&0x1ffff) );
  cnt &= 0x1ffff;
  do{
#if defined(USE_PREAD)
    got = osPread(id->h, pBuf, cnt, offset);
    SimulateIOError( got = -1 );
#elif defined(USE_PREAD64)
    got = osPread64(id->h, pBuf, cnt, offset);
    SimulateIOError( got = -1 );
#else
    newOffset = lseek(id->h, offset, SEEK_SET);
    SimulateIOError( newOffset-- );
    if( newOffset!=offset ){
      if( newOffset == -1 ){
        ((unixFile*)id)->lastErrno = errno;
      }else{
        ((unixFile*)id)->lastErrno = 0;
      }
      return -1;
    }
    got = osRead(id->h, pBuf, cnt);
#endif
    if( got==cnt ) break;
    if( got<0 ){
      if( errno==EINTR ){ got = 1; continue; }
      prior = 0;
      ((unixFile*)id)->lastErrno = errno;
      break;
    }else if( got>0 ){
      cnt -= got;
      offset += got;
      prior += got;
      pBuf = (void*)(got + (char*)pBuf);
    }
  }while( got>0 );
  TIMER_END;
  OSTRACE(("READ    %-3d %5d %7lld %llu\n",
            id->h, got+prior, offset-prior, TIMER_ELAPSED));
  return got+prior;
}