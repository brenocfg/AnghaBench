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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_4__ {int nResColumn; TYPE_2__* db; int /*<<< orphan*/ * pResultSet; } ;
typedef  TYPE_1__ Vdbe ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  Mem ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_RANGE ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 scalar_t__ columnNullValue () ; 
 int /*<<< orphan*/  sqlite3Error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Mem *columnMem(sqlite3_stmt *pStmt, int i){
  Vdbe *pVm;
  Mem *pOut;

  pVm = (Vdbe *)pStmt;
  if( pVm==0 ) return (Mem*)columnNullValue();
  assert( pVm->db );
  sqlite3_mutex_enter(pVm->db->mutex);
  if( pVm->pResultSet!=0 && i<pVm->nResColumn && i>=0 ){
    pOut = &pVm->pResultSet[i];
  }else{
    sqlite3Error(pVm->db, SQLITE_RANGE);
    pOut = (Mem*)columnNullValue();
  }
  return pOut;
}