#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_15__ {int wtFlags; TYPE_4__* pWC; } ;
typedef  TYPE_5__ WhereTerm ;
struct TYPE_16__ {int iLikeRepCntr; } ;
typedef  TYPE_6__ WhereLevel ;
struct TYPE_17__ {scalar_t__ opcode; int p3; scalar_t__ p5; } ;
typedef  TYPE_7__ VdbeOp ;
typedef  int /*<<< orphan*/  Vdbe ;
struct TYPE_14__ {TYPE_3__* pWInfo; } ;
struct TYPE_13__ {TYPE_2__* pParse; } ;
struct TYPE_12__ {TYPE_1__* db; } ;
struct TYPE_11__ {scalar_t__ mallocFailed; } ;

/* Variables and functions */
 scalar_t__ OP_String8 ; 
 int TERM_LIKEOPT ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_7__* sqlite3VdbeGetOp (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void whereLikeOptimizationStringFixup(
  Vdbe *v,                /* prepared statement under construction */
  WhereLevel *pLevel,     /* The loop that contains the LIKE operator */
  WhereTerm *pTerm        /* The upper or lower bound just coded */
){
  if( pTerm->wtFlags & TERM_LIKEOPT ){
    VdbeOp *pOp;
    assert( pLevel->iLikeRepCntr>0 );
    pOp = sqlite3VdbeGetOp(v, -1);
    assert( pOp!=0 );
    assert( pOp->opcode==OP_String8
            || pTerm->pWC->pWInfo->pParse->db->mallocFailed );
    pOp->p3 = (int)(pLevel->iLikeRepCntr>>1);  /* Register holding counter */
    pOp->p5 = (u8)(pLevel->iLikeRepCntr&1);    /* ASC or DESC */
  }
}