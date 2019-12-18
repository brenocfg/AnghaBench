#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_5__ {int /*<<< orphan*/ * pVdbe; } ;
typedef  TYPE_1__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  OP_Found ; 
 int /*<<< orphan*/  OP_IdxInsert ; 
 int /*<<< orphan*/  OP_MakeRecord ; 
 int sqlite3GetTempReg (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3ReleaseTempReg (TYPE_1__*,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp4Int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void codeDistinct(
  Parse *pParse,     /* Parsing and code generating context */
  int iTab,          /* A sorting index used to test for distinctness */
  int addrRepeat,    /* Jump to here if not distinct */
  int N,             /* Number of elements */
  int iMem           /* First element */
){
  Vdbe *v;
  int r1;

  v = pParse->pVdbe;
  r1 = sqlite3GetTempReg(pParse);
  sqlite3VdbeAddOp4Int(v, OP_Found, iTab, addrRepeat, iMem, N);
  sqlite3VdbeAddOp3(v, OP_MakeRecord, iMem, N, r1);
  sqlite3VdbeAddOp2(v, OP_IdxInsert, iTab, r1);
  sqlite3ReleaseTempReg(pParse, r1);
}