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
 int /*<<< orphan*/  OP_Halt ; 
 int /*<<< orphan*/  OP_IfPos ; 
 int /*<<< orphan*/  OP_ResultRow ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 scalar_t__ sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int integrityCheckResultRow(Vdbe *v, int regResult){
  int addr;
  sqlite3VdbeAddOp2(v, OP_ResultRow, regResult, 1);
  addr = sqlite3VdbeAddOp3(v, OP_IfPos, 1, sqlite3VdbeCurrentAddr(v)+2, 1);
  VdbeCoverage(v);
  sqlite3VdbeAddOp2(v, OP_Halt, 0, 0);
  return addr;
}