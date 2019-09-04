#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_uint64 ;
struct TYPE_9__ {TYPE_2__* pOut; } ;
typedef  TYPE_3__ sqlite3_context ;
struct TYPE_8__ {TYPE_1__* db; } ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 void SQLITE_DYNAMIC (void*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  invokeValueDestructor (void const*,void (*) (void*),TYPE_3__*) ; 
 int /*<<< orphan*/  setResultStrOrError (TYPE_3__*,void const*,int,int /*<<< orphan*/ ,void (*) (void*)) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

void sqlite3_result_blob64(
  sqlite3_context *pCtx,
  const void *z,
  sqlite3_uint64 n,
  void (*xDel)(void *)
){
  assert( sqlite3_mutex_held(pCtx->pOut->db->mutex) );
  assert( xDel!=SQLITE_DYNAMIC );
  if( n>0x7fffffff ){
    (void)invokeValueDestructor(z, xDel, pCtx);
  }else{
    setResultStrOrError(pCtx, z, (int)n, 0, xDel);
  }
}