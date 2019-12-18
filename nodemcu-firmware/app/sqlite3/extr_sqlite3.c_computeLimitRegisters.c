#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_9__ {int nMem; } ;
struct TYPE_8__ {int iLimit; scalar_t__ nSelectRow; int iOffset; int /*<<< orphan*/  pOffset; int /*<<< orphan*/  pLimit; int /*<<< orphan*/  selFlags; } ;
typedef  TYPE_1__ Select ;
typedef  TYPE_2__ Parse ;

/* Variables and functions */
 int /*<<< orphan*/  OP_IfNot ; 
 int /*<<< orphan*/  OP_Integer ; 
 int /*<<< orphan*/  OP_MustBeInt ; 
 int /*<<< orphan*/  OP_OffsetLimit ; 
 int /*<<< orphan*/  SF_FixedLimit ; 
 int /*<<< orphan*/  VdbeComment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VdbeCoverage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ExprCacheClear (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3ExprCode (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3ExprIsInteger (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * sqlite3GetVdbe (TYPE_2__*) ; 
 scalar_t__ sqlite3LogEst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeAddOp3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sqlite3VdbeGoto (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void computeLimitRegisters(Parse *pParse, Select *p, int iBreak){
  Vdbe *v = 0;
  int iLimit = 0;
  int iOffset;
  int n;
  if( p->iLimit ) return;

  /*
  ** "LIMIT -1" always shows all rows.  There is some
  ** controversy about what the correct behavior should be.
  ** The current implementation interprets "LIMIT 0" to mean
  ** no rows.
  */
  sqlite3ExprCacheClear(pParse);
  assert( p->pOffset==0 || p->pLimit!=0 );
  if( p->pLimit ){
    p->iLimit = iLimit = ++pParse->nMem;
    v = sqlite3GetVdbe(pParse);
    assert( v!=0 );
    if( sqlite3ExprIsInteger(p->pLimit, &n) ){
      sqlite3VdbeAddOp2(v, OP_Integer, n, iLimit);
      VdbeComment((v, "LIMIT counter"));
      if( n==0 ){
        sqlite3VdbeGoto(v, iBreak);
      }else if( n>=0 && p->nSelectRow>sqlite3LogEst((u64)n) ){
        p->nSelectRow = sqlite3LogEst((u64)n);
        p->selFlags |= SF_FixedLimit;
      }
    }else{
      sqlite3ExprCode(pParse, p->pLimit, iLimit);
      sqlite3VdbeAddOp1(v, OP_MustBeInt, iLimit); VdbeCoverage(v);
      VdbeComment((v, "LIMIT counter"));
      sqlite3VdbeAddOp2(v, OP_IfNot, iLimit, iBreak); VdbeCoverage(v);
    }
    if( p->pOffset ){
      p->iOffset = iOffset = ++pParse->nMem;
      pParse->nMem++;   /* Allocate an extra register for limit+offset */
      sqlite3ExprCode(pParse, p->pOffset, iOffset);
      sqlite3VdbeAddOp1(v, OP_MustBeInt, iOffset); VdbeCoverage(v);
      VdbeComment((v, "OFFSET counter"));
      sqlite3VdbeAddOp3(v, OP_OffsetLimit, iLimit, iOffset+1, iOffset);
      VdbeComment((v, "LIMIT+OFFSET"));
    }
  }
}