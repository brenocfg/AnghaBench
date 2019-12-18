#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_6__ {int* aLabel; int readOnly; int nOp; int nLabel; int /*<<< orphan*/  db; TYPE_3__* aOp; } ;
typedef  TYPE_2__ Vdbe ;
struct TYPE_5__ {int /*<<< orphan*/  xAdvance; } ;
struct TYPE_7__ {size_t opcode; int opflags; int p5; int p2; int p1; void* p4type; TYPE_1__ p4; } ;
typedef  TYPE_3__ Op ;

/* Variables and functions */
 int OPFLG_JUMP ; 
 size_t OP_AggStep ; 
 size_t OP_Function ; 
 scalar_t__ OP_Integer ; 
 size_t OP_Next ; 
 size_t OP_Prev ; 
 size_t OP_SorterNext ; 
 size_t OP_Transaction ; 
 size_t OP_VFilter ; 
 size_t OP_VUpdate ; 
 size_t OP_Vacuum ; 
 void* P4_ADVANCE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3BtreeNext ; 
 int /*<<< orphan*/  sqlite3BtreePrevious ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ ,int*) ; 
 int* sqlite3OpcodeProperty ; 

__attribute__((used)) static void resolveP2Values(Vdbe *p, int *pMaxFuncArgs){
  int i;
  int nMaxArgs = *pMaxFuncArgs;
  Op *pOp;
  int *aLabel = p->aLabel;
  p->readOnly = 1;
  for(pOp=p->aOp, i=p->nOp-1; i>=0; i--, pOp++){
    u8 opcode = pOp->opcode;

    pOp->opflags = sqlite3OpcodeProperty[opcode];
    if( opcode==OP_Function || opcode==OP_AggStep ){
      if( pOp->p5>nMaxArgs ) nMaxArgs = pOp->p5;
    }else if( (opcode==OP_Transaction && pOp->p2!=0) || opcode==OP_Vacuum ){
      p->readOnly = 0;
#ifndef SQLITE_OMIT_VIRTUALTABLE
    }else if( opcode==OP_VUpdate ){
      if( pOp->p2>nMaxArgs ) nMaxArgs = pOp->p2;
    }else if( opcode==OP_VFilter ){
      int n;
      assert( p->nOp - i >= 3 );
      assert( pOp[-1].opcode==OP_Integer );
      n = pOp[-1].p1;
      if( n>nMaxArgs ) nMaxArgs = n;
#endif
    }else if( opcode==OP_Next || opcode==OP_SorterNext ){
      pOp->p4.xAdvance = sqlite3BtreeNext;
      pOp->p4type = P4_ADVANCE;
    }else if( opcode==OP_Prev ){
      pOp->p4.xAdvance = sqlite3BtreePrevious;
      pOp->p4type = P4_ADVANCE;
    }

    if( (pOp->opflags & OPFLG_JUMP)!=0 && pOp->p2<0 ){
      assert( -1-pOp->p2<p->nLabel );
      pOp->p2 = aLabel[-1-pOp->p2];
    }
  }
  sqlite3DbFree(p->db, p->aLabel);
  p->aLabel = 0;

  *pMaxFuncArgs = nMaxArgs;
}