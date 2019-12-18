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
typedef  int i64 ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  OSTRACE (char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SimulateIOError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TIMER_ELAPSED ; 
 int /*<<< orphan*/  TIMER_END ; 
 int /*<<< orphan*/  TIMER_START ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int lseek (int,int,int /*<<< orphan*/ ) ; 
 int osPwrite (int,void const*,int,int) ; 
 int osPwrite64 (int,void const*,int,int) ; 
 int osWrite (int,void const*,int) ; 

__attribute__((used)) static int seekAndWriteFd(
  int fd,                         /* File descriptor to write to */
  i64 iOff,                       /* File offset to begin writing at */
  const void *pBuf,               /* Copy data from this buffer to the file */
  int nBuf,                       /* Size of buffer pBuf in bytes */
  int *piErrno                    /* OUT: Error number if error occurs */
){
  int rc = 0;                     /* Value returned by system call */

  assert( nBuf==(nBuf&0x1ffff) );
  nBuf &= 0x1ffff;
  TIMER_START;

#if defined(USE_PREAD)
  do{ rc = osPwrite(fd, pBuf, nBuf, iOff); }while( rc<0 && errno==EINTR );
#elif defined(USE_PREAD64)
  do{ rc = osPwrite64(fd, pBuf, nBuf, iOff);}while( rc<0 && errno==EINTR);
#else
  do{
    i64 iSeek = lseek(fd, iOff, SEEK_SET);
    SimulateIOError( iSeek-- );

    if( iSeek!=iOff ){
      if( piErrno ) *piErrno = (iSeek==-1 ? errno : 0);
      return -1;
    }
    rc = osWrite(fd, pBuf, nBuf);
  }while( rc<0 && errno==EINTR );
#endif

  TIMER_END;
  OSTRACE(("WRITE   %-3d %5d %7lld %llu\n", fd, rc, iOff, TIMER_ELAPSED));

  if( rc<0 && piErrno ) *piErrno = errno;
  return rc;
}