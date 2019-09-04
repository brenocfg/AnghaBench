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
typedef  char u8 ;
struct TYPE_2__ {int isInit; size_t j; size_t i; char* s; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  sqlite3OsRandomness (int /*<<< orphan*/ ,int,char*) ; 
 TYPE_1__ sqlite3Prng ; 
 scalar_t__ sqlite3_initialize () ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_vfs_find (int /*<<< orphan*/ ) ; 

void sqlite3_randomness(int N, void *pBuf){
  unsigned char t;
  unsigned char *zBuf = pBuf;

  /* The "wsdPrng" macro will resolve to the pseudo-random number generator
  ** state vector.  If writable static data is unsupported on the target,
  ** we have to locate the state vector at run-time.  In the more common
  ** case where writable static data is supported, wsdPrng can refer directly
  ** to the "sqlite3Prng" state vector declared above.
  */
#ifdef SQLITE_OMIT_WSD
  struct sqlite3PrngType *p = &GLOBAL(struct sqlite3PrngType, sqlite3Prng);
# define wsdPrng p[0]
#else
# define wsdPrng sqlite3Prng
#endif

#if SQLITE_THREADSAFE
  sqlite3_mutex *mutex;
#endif

#ifndef SQLITE_OMIT_AUTOINIT
  if( sqlite3_initialize() ) return;
#endif

#if SQLITE_THREADSAFE
  mutex = sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_PRNG);
#endif

  sqlite3_mutex_enter(mutex);
  if( N<=0 || pBuf==0 ){
    wsdPrng.isInit = 0;
    sqlite3_mutex_leave(mutex);
    return;
  }

  /* Initialize the state of the random number generator once,
  ** the first time this routine is called.  The seed value does
  ** not need to contain a lot of randomness since we are not
  ** trying to do secure encryption or anything like that...
  **
  ** Nothing in this file or anywhere else in SQLite does any kind of
  ** encryption.  The RC4 algorithm is being used as a PRNG (pseudo-random
  ** number generator) not as an encryption device.
  */
  if( !wsdPrng.isInit ){
    int i;
    char k[256];
    wsdPrng.j = 0;
    wsdPrng.i = 0;
    sqlite3OsRandomness(sqlite3_vfs_find(0), 256, k);
    for(i=0; i<256; i++){
      wsdPrng.s[i] = (u8)i;
    }
    for(i=0; i<256; i++){
      wsdPrng.j += wsdPrng.s[i] + k[i];
      t = wsdPrng.s[wsdPrng.j];
      wsdPrng.s[wsdPrng.j] = wsdPrng.s[i];
      wsdPrng.s[i] = t;
    }
    wsdPrng.isInit = 1;
  }

  assert( N>0 );
  do{
    wsdPrng.i++;
    t = wsdPrng.s[wsdPrng.i];
    wsdPrng.j += t;
    wsdPrng.s[wsdPrng.i] = wsdPrng.s[wsdPrng.j];
    wsdPrng.s[wsdPrng.j] = t;
    t += wsdPrng.s[wsdPrng.i];
    *(zBuf++) = wsdPrng.s[t];
  }while( --N );
  sqlite3_mutex_leave(mutex);
}