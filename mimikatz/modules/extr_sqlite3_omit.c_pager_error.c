#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int errCode; int /*<<< orphan*/  eState; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int /*<<< orphan*/  MEMDB ; 
 int /*<<< orphan*/  PAGER_ERROR ; 
 int SQLITE_FULL ; 
 int SQLITE_IOERR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  setGetterMethod (TYPE_1__*) ; 

__attribute__((used)) static int pager_error(Pager *pPager, int rc){
  int rc2 = rc & 0xff;
  assert( rc==SQLITE_OK || !MEMDB );
  assert(
       pPager->errCode==SQLITE_FULL ||
       pPager->errCode==SQLITE_OK ||
       (pPager->errCode & 0xff)==SQLITE_IOERR
  );
  if( rc2==SQLITE_FULL || rc2==SQLITE_IOERR ){
    pPager->errCode = rc;
    pPager->eState = PAGER_ERROR;
    setGetterMethod(pPager);
  }
  return rc;
}