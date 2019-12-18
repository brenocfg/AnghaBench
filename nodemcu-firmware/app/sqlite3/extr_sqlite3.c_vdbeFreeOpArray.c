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
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {int /*<<< orphan*/  p; } ;
struct TYPE_6__ {int /*<<< orphan*/  zComment; TYPE_1__ p4; scalar_t__ p4type; } ;
typedef  TYPE_2__ Op ;

/* Variables and functions */
 int /*<<< orphan*/  freeP4 (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DbFreeNN (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void vdbeFreeOpArray(sqlite3 *db, Op *aOp, int nOp){
  if( aOp ){
    Op *pOp;
    for(pOp=&aOp[nOp-1]; pOp>=aOp; pOp--){
      if( pOp->p4type ) freeP4(db, pOp->p4type, pOp->p4.p);
#ifdef SQLITE_ENABLE_EXPLAIN_COMMENTS
      sqlite3DbFree(db, pOp->zComment);
#endif
    }
    sqlite3DbFreeNN(db, aOp);
  }
}