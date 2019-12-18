#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int p1; scalar_t__ opcode; int p2; int p3; } ;
typedef  TYPE_2__ VdbeOp ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_8__ {TYPE_1__* db; int /*<<< orphan*/ * pVdbe; } ;
struct TYPE_6__ {scalar_t__ mallocFailed; } ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */
 scalar_t__ OP_AddImm ; 
 scalar_t__ OP_Column ; 
 scalar_t__ OP_Copy ; 
 scalar_t__ OP_Null ; 
 scalar_t__ OP_Rowid ; 
 int sqlite3VdbeCurrentAddr (int /*<<< orphan*/ *) ; 
 TYPE_2__* sqlite3VdbeGetOp (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void translateColumnToCopy(
  Parse *pParse,      /* Parsing context */
  int iStart,         /* Translate from this opcode to the end */
  int iTabCur,        /* OP_Column/OP_Rowid references to this table */
  int iRegister,      /* The first column is in this register */
  int bIncrRowid      /* If non-zero, transform OP_rowid to OP_AddImm(1) */
){
  Vdbe *v = pParse->pVdbe;
  VdbeOp *pOp = sqlite3VdbeGetOp(v, iStart);
  int iEnd = sqlite3VdbeCurrentAddr(v);
  if( pParse->db->mallocFailed ) return;
  for(; iStart<iEnd; iStart++, pOp++){
    if( pOp->p1!=iTabCur ) continue;
    if( pOp->opcode==OP_Column ){
      pOp->opcode = OP_Copy;
      pOp->p1 = pOp->p2 + iRegister;
      pOp->p2 = pOp->p3;
      pOp->p3 = 0;
    }else if( pOp->opcode==OP_Rowid ){
      if( bIncrRowid ){
        /* Increment the value stored in the P2 operand of the OP_Rowid. */
        pOp->opcode = OP_AddImm;
        pOp->p1 = pOp->p2;
        pOp->p2 = 1;
      }else{
        pOp->opcode = OP_Null;
        pOp->p1 = 0;
        pOp->p3 = 0;
      }
    }
  }
}