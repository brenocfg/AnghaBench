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
typedef  int /*<<< orphan*/  Vdbe ;

/* Variables and functions */
 scalar_t__ IsStat34 ; 
 int /*<<< orphan*/  OP_Function0 ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  P4_FUNCDEF ; 
 int STAT_GET_STAT1 ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  statGetFuncdef ; 

__attribute__((used)) static void callStatGet(Vdbe *v, int regStat4, int iParam, int regOut){
  assert( regOut!=regStat4 && regOut!=regStat4+1 );
#ifdef SQLITE_ENABLE_STAT3_OR_STAT4
  sqlite3VdbeAddOp2(v, OP_Integer, iParam, regStat4+1);
#elif SQLITE_DEBUG
  assert( iParam==STAT_GET_STAT1 );
#else
  UNUSED_PARAMETER( iParam );
#endif
  sqlite3VdbeAddOp4(v, OP_Function0, 0, regStat4, regOut,
                    (char*)&statGetFuncdef, P4_FUNCDEF);
  sqlite3VdbeChangeP5(v, 1 + IsStat34);
}