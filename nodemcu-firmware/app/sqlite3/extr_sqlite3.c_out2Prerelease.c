#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {size_t p2; } ;
typedef  TYPE_1__ VdbeOp ;
struct TYPE_13__ {size_t nMem; size_t nCursor; TYPE_3__* aMem; } ;
typedef  TYPE_2__ Vdbe ;
struct TYPE_14__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ Mem ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_Int ; 
 scalar_t__ VdbeMemDynamic (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memAboutToChange (TYPE_2__*,TYPE_3__*) ; 
 TYPE_3__* out2PrereleaseWithClear (TYPE_3__*) ; 

__attribute__((used)) static Mem *out2Prerelease(Vdbe *p, VdbeOp *pOp){
  Mem *pOut;
  assert( pOp->p2>0 );
  assert( pOp->p2<=(p->nMem+1 - p->nCursor) );
  pOut = &p->aMem[pOp->p2];
  memAboutToChange(p, pOut);
  if( VdbeMemDynamic(pOut) ){ /*OPTIMIZATION-IF-FALSE*/
    return out2PrereleaseWithClear(pOut);
  }else{
    pOut->flags = MEM_Int;
    return pOut;
  }
}