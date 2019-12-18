#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct TYPE_4__ {size_t n; TYPE_2__* a; } ;
typedef  TYPE_1__ WhereOrSet ;
struct TYPE_5__ {scalar_t__ rRun; int prereq; scalar_t__ nOut; } ;
typedef  TYPE_2__ WhereOrCost ;
typedef  scalar_t__ LogEst ;
typedef  int Bitmask ;

/* Variables and functions */
 size_t N_OR_COST ; 

__attribute__((used)) static int whereOrInsert(
  WhereOrSet *pSet,      /* The WhereOrSet to be updated */
  Bitmask prereq,        /* Prerequisites of the new entry */
  LogEst rRun,           /* Run-cost of the new entry */
  LogEst nOut            /* Number of outputs for the new entry */
){
  u16 i;
  WhereOrCost *p;
  for(i=pSet->n, p=pSet->a; i>0; i--, p++){
    if( rRun<=p->rRun && (prereq & p->prereq)==prereq ){
      goto whereOrInsert_done;
    }
    if( p->rRun<=rRun && (p->prereq & prereq)==p->prereq ){
      return 0;
    }
  }
  if( pSet->n<N_OR_COST ){
    p = &pSet->a[pSet->n++];
    p->nOut = nOut;
  }else{
    p = pSet->a;
    for(i=1; i<pSet->n; i++){
      if( p->rRun>pSet->a[i].rRun ) p = pSet->a + i;
    }
    if( p->rRun<=rRun ) return 0;
  }
whereOrInsert_done:
  p->prereq = prereq;
  p->rRun = rRun;
  if( p->nOut>nOut ) p->nOut = nOut;
  return 1;
}