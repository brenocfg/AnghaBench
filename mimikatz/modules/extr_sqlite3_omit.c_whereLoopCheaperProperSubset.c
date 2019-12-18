#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int nLTerm; scalar_t__ nSkip; scalar_t__ rRun; scalar_t__ nOut; scalar_t__* aLTerm; int wsFlags; } ;
typedef  TYPE_1__ WhereLoop ;

/* Variables and functions */
 int WHERE_IDX_ONLY ; 

__attribute__((used)) static int whereLoopCheaperProperSubset(
  const WhereLoop *pX,       /* First WhereLoop to compare */
  const WhereLoop *pY        /* Compare against this WhereLoop */
){
  int i, j;
  if( pX->nLTerm-pX->nSkip >= pY->nLTerm-pY->nSkip ){
    return 0; /* X is not a subset of Y */
  }
  if( pY->nSkip > pX->nSkip ) return 0;
  if( pX->rRun >= pY->rRun ){
    if( pX->rRun > pY->rRun ) return 0;    /* X costs more than Y */
    if( pX->nOut > pY->nOut ) return 0;    /* X costs more than Y */
  }
  for(i=pX->nLTerm-1; i>=0; i--){
    if( pX->aLTerm[i]==0 ) continue;
    for(j=pY->nLTerm-1; j>=0; j--){
      if( pY->aLTerm[j]==pX->aLTerm[i] ) break;
    }
    if( j<0 ) return 0;  /* X not a subset of Y since term X[i] not used by Y */
  }
  if( (pX->wsFlags&WHERE_IDX_ONLY)!=0 
   && (pY->wsFlags&WHERE_IDX_ONLY)==0 ){
    return 0;  /* Constraint (5) */
  }
  return 1;  /* All conditions meet */
}