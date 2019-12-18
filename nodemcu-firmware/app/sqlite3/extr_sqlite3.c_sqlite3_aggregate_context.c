#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* pMem; TYPE_3__* pOut; TYPE_1__* pFunc; } ;
typedef  TYPE_5__ sqlite3_context ;
struct TYPE_11__ {int flags; scalar_t__ z; } ;
struct TYPE_10__ {TYPE_2__* db; } ;
struct TYPE_9__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_8__ {scalar_t__ xFinalize; } ;

/* Variables and functions */
 int MEM_Agg ; 
 int /*<<< orphan*/  assert (int) ; 
 void* createAggContext (TYPE_5__*,int) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

void *sqlite3_aggregate_context(sqlite3_context *p, int nByte){
  assert( p && p->pFunc && p->pFunc->xFinalize );
  assert( sqlite3_mutex_held(p->pOut->db->mutex) );
  testcase( nByte<0 );
  if( (p->pMem->flags & MEM_Agg)==0 ){
    return createAggContext(p, nByte);
  }else{
    return (void*)p->pMem->z;
  }
}