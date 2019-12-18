#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {scalar_t__* apCsr; int nCursor; int nMem; scalar_t__ pResultSet; int /*<<< orphan*/  zErrMsg; TYPE_1__* aMem; int /*<<< orphan*/ * db; } ;
typedef  TYPE_2__ Vdbe ;
struct TYPE_4__ {scalar_t__ flags; } ;

/* Variables and functions */
 scalar_t__ MEM_Invalid ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Cleanup(Vdbe *p){
  sqlite3 *db = p->db;

#ifdef SQLITE_DEBUG
  /* Execute assert() statements to ensure that the Vdbe.apCsr[] and 
  ** Vdbe.aMem[] arrays have already been cleaned up.  */
  int i;
  if( p->apCsr ) for(i=0; i<p->nCursor; i++) assert( p->apCsr[i]==0 );
  if( p->aMem ){
    for(i=1; i<=p->nMem; i++) assert( p->aMem[i].flags==MEM_Invalid );
  }
#endif

  sqlite3DbFree(db, p->zErrMsg);
  p->zErrMsg = 0;
  p->pResultSet = 0;
}