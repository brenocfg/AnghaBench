#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* pMWin; TYPE_5__* pParse; } ;
typedef  TYPE_4__ WindowCodeArg ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_15__ {int nMem; } ;
struct TYPE_13__ {TYPE_2__* pOrderBy; } ;
struct TYPE_12__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_11__ {scalar_t__ sortOrder; } ;
typedef  TYPE_5__ Parse ;

/* Variables and functions */
 int OP_Add ; 
#define  OP_Ge 129 
#define  OP_Gt 128 
 int OP_Le ; 
 int OP_Lt ; 
 int /*<<< orphan*/  OP_String8 ; 
 int OP_Subtract ; 
 int /*<<< orphan*/  P4_STATIC ; 
 int /*<<< orphan*/  SQLITE_NULLEQ ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverageIf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3GetTempReg (TYPE_5__*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_5__*,int) ; 
 int sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeChangeP5 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeJumpHere (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testcase (int) ; 
 int /*<<< orphan*/  windowReadPeerValues (TYPE_4__*,int,int) ; 

__attribute__((used)) static void windowCodeRangeTest(
  WindowCodeArg *p, 
  int op,                          /* OP_Ge or OP_Gt */
  int csr1, 
  int regVal, 
  int csr2,
  int lbl
){
  Parse *pParse = p->pParse;
  Vdbe *v = sqlite3GetVdbe(pParse);
  int reg1 = sqlite3GetTempReg(pParse);
  int reg2 = sqlite3GetTempReg(pParse);
  int arith = OP_Add;
  int addrGe;

  int regString = ++pParse->nMem;

  assert( op==OP_Ge || op==OP_Gt || op==OP_Le );
  assert( p->pMWin->pOrderBy && p->pMWin->pOrderBy->nExpr==1 );
  if( p->pMWin->pOrderBy->a[0].sortOrder ){
    switch( op ){
      case OP_Ge: op = OP_Le; break;
      case OP_Gt: op = OP_Lt; break;
      default: assert( op==OP_Le ); op = OP_Ge; break;
    }
    arith = OP_Subtract;
  }

  windowReadPeerValues(p, csr1, reg1);
  windowReadPeerValues(p, csr2, reg2);

  /* Check if the peer value for csr1 value is a text or blob by comparing
  ** it to the smallest possible string - ''. If it is, jump over the
  ** OP_Add or OP_Subtract operation and proceed directly to the comparison. */
  sqlite3VdbeAddOp4(v, OP_String8, 0, regString, 0, "", P4_STATIC);
  addrGe = sqlite3VdbeAddOp3(v, OP_Ge, regString, 0, reg1);
  VdbeCoverage(v);
  sqlite3VdbeAddOp3(v, arith, regVal, reg1, reg1);
  sqlite3VdbeJumpHere(v, addrGe);
  sqlite3VdbeAddOp3(v, op, reg2, lbl, reg1); VdbeCoverage(v);
  sqlite3VdbeChangeP5(v, SQLITE_NULLEQ);
  assert( op==OP_Ge || op==OP_Gt || op==OP_Lt || op==OP_Le );
  testcase(op==OP_Ge); VdbeCoverageIf(v, op==OP_Ge);
  testcase(op==OP_Lt); VdbeCoverageIf(v, op==OP_Lt);
  testcase(op==OP_Le); VdbeCoverageIf(v, op==OP_Le);
  testcase(op==OP_Gt); VdbeCoverageIf(v, op==OP_Gt);

  sqlite3ReleaseTempReg(pParse, reg1);
  sqlite3ReleaseTempReg(pParse, reg2);
}