#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_12__ {TYPE_2__* db; } ;
struct TYPE_11__ {TYPE_1__* aDb; } ;
struct TYPE_10__ {int /*<<< orphan*/  zDbSName; } ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  MASTER_NAME ; 
 int /*<<< orphan*/  OP_Destroy ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3GetTempReg (TYPE_3__*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3MayAbort (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3NestedParse (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void destroyRootPage(Parse *pParse, int iTable, int iDb){
  Vdbe *v = sqlite3GetVdbe(pParse);
  int r1 = sqlite3GetTempReg(pParse);
  assert( iTable>1 );
  sqlite3VdbeAddOp3(v, OP_Destroy, iTable, r1, iDb);
  sqlite3MayAbort(pParse);
#ifndef SQLITE_OMIT_AUTOVACUUM
  /* OP_Destroy stores an in integer r1. If this integer
  ** is non-zero, then it is the root page number of a table moved to
  ** location iTable. The following code modifies the sqlite_master table to
  ** reflect this.
  **
  ** The "#NNN" in the SQL is a special constant that means whatever value
  ** is in register NNN.  See grammar rules associated with the TK_REGISTER
  ** token for additional information.
  */
  sqlite3NestedParse(pParse,
     "UPDATE %Q.%s SET rootpage=%d WHERE #%d AND rootpage=#%d",
     pParse->db->aDb[iDb].zDbSName, MASTER_NAME, iTable, r1, r1);
#endif
  sqlite3ReleaseTempReg(pParse, r1);
}