#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int readOnly; int bIsReader; int nOp; int /*<<< orphan*/  btreeMask; int /*<<< orphan*/  db; TYPE_4__* aOp; TYPE_3__* pParse; } ;
typedef  TYPE_2__ Vdbe ;
struct TYPE_6__ {int /*<<< orphan*/  xAdvance; } ;
struct TYPE_9__ {int opcode; int p2; int p1; void* p4type; TYPE_1__ p4; } ;
struct TYPE_8__ {int* aLabel; size_t nLabel; } ;
typedef  TYPE_3__ Parse ;
typedef  TYPE_4__ Op ;

/* Variables and functions */
 size_t ADDR (int) ; 
 scalar_t__ DbMaskAllZero (int /*<<< orphan*/ ) ; 
 int OPFLG_JUMP ; 
#define  OP_AutoCommit 140 
#define  OP_Checkpoint 139 
 int OP_Integer ; 
#define  OP_JournalMode 138 
#define  OP_Next 137 
#define  OP_NextIfOpen 136 
#define  OP_Prev 135 
#define  OP_PrevIfOpen 134 
#define  OP_Savepoint 133 
#define  OP_SorterNext 132 
#define  OP_Transaction 131 
#define  OP_VFilter 130 
#define  OP_VUpdate 129 
#define  OP_Vacuum 128 
 void* P4_ADVANCE ; 
 int SQLITE_MX_JUMP_OPCODE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3BtreeNext ; 
 int /*<<< orphan*/  sqlite3BtreePrevious ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ ,int*) ; 
 int* sqlite3OpcodeProperty ; 

__attribute__((used)) static void resolveP2Values(Vdbe *p, int *pMaxFuncArgs){
  int nMaxArgs = *pMaxFuncArgs;
  Op *pOp;
  Parse *pParse = p->pParse;
  int *aLabel = pParse->aLabel;
  p->readOnly = 1;
  p->bIsReader = 0;
  pOp = &p->aOp[p->nOp-1];
  while(1){

    /* Only JUMP opcodes and the short list of special opcodes in the switch
    ** below need to be considered.  The mkopcodeh.tcl generator script groups
    ** all these opcodes together near the front of the opcode list.  Skip
    ** any opcode that does not need processing by virtual of the fact that
    ** it is larger than SQLITE_MX_JUMP_OPCODE, as a performance optimization.
    */
    if( pOp->opcode<=SQLITE_MX_JUMP_OPCODE ){
      /* NOTE: Be sure to update mkopcodeh.tcl when adding or removing
      ** cases from this switch! */
      switch( pOp->opcode ){
        case OP_Transaction: {
          if( pOp->p2!=0 ) p->readOnly = 0;
          /* fall thru */
        }
        case OP_AutoCommit:
        case OP_Savepoint: {
          p->bIsReader = 1;
          break;
        }
#ifndef SQLITE_OMIT_WAL
        case OP_Checkpoint:
#endif
        case OP_Vacuum:
        case OP_JournalMode: {
          p->readOnly = 0;
          p->bIsReader = 1;
          break;
        }
#ifndef SQLITE_OMIT_VIRTUALTABLE
        case OP_VUpdate: {
          if( pOp->p2>nMaxArgs ) nMaxArgs = pOp->p2;
          break;
        }
        case OP_VFilter: {
          int n;
          assert( (pOp - p->aOp) >= 3 );
          assert( pOp[-1].opcode==OP_Integer );
          n = pOp[-1].p1;
          if( n>nMaxArgs ) nMaxArgs = n;
          break;
        }
#endif
        case OP_Next:
        case OP_NextIfOpen:
        case OP_SorterNext: {
          pOp->p4.xAdvance = sqlite3BtreeNext;
          pOp->p4type = P4_ADVANCE;
          break;
        }
        case OP_Prev:
        case OP_PrevIfOpen: {
          pOp->p4.xAdvance = sqlite3BtreePrevious;
          pOp->p4type = P4_ADVANCE;
          break;
        }
      }
      if( (sqlite3OpcodeProperty[pOp->opcode] & OPFLG_JUMP)!=0 && pOp->p2<0 ){
        assert( ADDR(pOp->p2)<pParse->nLabel );
        pOp->p2 = aLabel[ADDR(pOp->p2)];
      }
    }
    if( pOp==p->aOp ) break;
    pOp--;
  }
  sqlite3DbFree(p->db, pParse->aLabel);
  pParse->aLabel = 0;
  pParse->nLabel = 0;
  *pMaxFuncArgs = nMaxArgs;
  assert( p->bIsReader!=0 || DbMaskAllZero(p->btreeMask) );
}