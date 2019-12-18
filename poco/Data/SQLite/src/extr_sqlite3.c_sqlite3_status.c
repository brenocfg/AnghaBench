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
 int SQLITE_MISUSE_BKPT ; 
 int sqlite3_status64 (int,scalar_t__*,scalar_t__*,int) ; 

int sqlite3_status(int op, int *pCurrent, int *pHighwater, int resetFlag){
  sqlite3_int64 iCur = 0, iHwtr = 0;
  int rc;
#ifdef SQLITE_ENABLE_API_ARMOR
  if( pCurrent==0 || pHighwater==0 ) return SQLITE_MISUSE_BKPT;
#endif
  rc = sqlite3_status64(op, &iCur, &iHwtr, resetFlag);
  if( rc==0 ){
    *pCurrent = (int)iCur;
    *pHighwater = (int)iHwtr;
  }
  return rc;
}