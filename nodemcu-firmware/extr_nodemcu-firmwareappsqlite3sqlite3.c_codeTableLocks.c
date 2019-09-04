#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_5__ {int iDb; int /*<<< orphan*/  zLockName; int /*<<< orphan*/  isWriteLock; int /*<<< orphan*/  iTab; } ;
typedef  TYPE_1__ TableLock ;
struct TYPE_6__ {int nTableLock; TYPE_1__* aTableLock; } ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  OP_TableLock ; 
 int /*<<< orphan*/  P4_STATIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void codeTableLocks(Parse *pParse){
  int i;
  Vdbe *pVdbe;

  pVdbe = sqlite3GetVdbe(pParse);
  assert( pVdbe!=0 ); /* sqlite3GetVdbe cannot fail: VDBE already allocated */

  for(i=0; i<pParse->nTableLock; i++){
    TableLock *p = &pParse->aTableLock[i];
    int p1 = p->iDb;
    sqlite3VdbeAddOp4(pVdbe, OP_TableLock, p1, p->iTab, p->isWriteLock,
                      p->zLockName, P4_STATIC);
  }
}