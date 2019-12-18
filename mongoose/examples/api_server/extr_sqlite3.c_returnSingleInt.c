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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  i64 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_4__ {int nMem; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  COLNAME_NAME ; 
 int /*<<< orphan*/  OP_Int64 ; 
 int /*<<< orphan*/  OP_ResultRow ; 
 int /*<<< orphan*/  P4_INT64 ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sqlite3DbMallocRaw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeSetColName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeSetNumCols (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void returnSingleInt(Parse *pParse, const char *zLabel, i64 value){
  Vdbe *v = sqlite3GetVdbe(pParse);
  int mem = ++pParse->nMem;
  i64 *pI64 = sqlite3DbMallocRaw(pParse->db, sizeof(value));
  if( pI64 ){
    memcpy(pI64, &value, sizeof(value));
  }
  sqlite3VdbeAddOp4(v, OP_Int64, 0, mem, 0, (char*)pI64, P4_INT64);
  sqlite3VdbeSetNumCols(v, 1);
  sqlite3VdbeSetColName(v, 0, COLNAME_NAME, zLabel, SQLITE_STATIC);
  sqlite3VdbeAddOp2(v, OP_ResultRow, mem, 1);
}