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
typedef  scalar_t__ sqlite3_int64 ;

/* Variables and functions */

__attribute__((used)) static int sqlite3MemSize(void *pPrior){
#ifdef SQLITE_MALLOCSIZE
  return pPrior ? (int)SQLITE_MALLOCSIZE(pPrior) : 0;
#else
  sqlite3_int64 *p;
  if( pPrior==0 ) return 0;
  p = (sqlite3_int64*)pPrior;
  p--;
  return (int)p[0];
#endif
}