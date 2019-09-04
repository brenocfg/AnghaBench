#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Stat4Accum ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 

__attribute__((used)) static void samplePushPrevious(Stat4Accum *p, int iChng){
#ifdef SQLITE_ENABLE_STAT4
  int i;

  /* Check if any samples from the aBest[] array should be pushed
  ** into IndexSample.a[] at this point.  */
  for(i=(p->nCol-2); i>=iChng; i--){
    Stat4Sample *pBest = &p->aBest[i];
    pBest->anEq[i] = p->current.anEq[i];
    if( p->nSample<p->mxSample || sampleIsBetter(p, pBest, &p->a[p->iMin]) ){
      sampleInsert(p, pBest, i);
    }
  }

  /* Check that no sample contains an anEq[] entry with an index of
  ** p->nMaxEqZero or greater set to zero. */
  for(i=p->nSample-1; i>=0; i--){
    int j;
    for(j=p->nMaxEqZero; j<p->nCol; j++) assert( p->a[i].anEq[j]>0 );
  }

  /* Update the anEq[] fields of any samples already collected. */
  if( iChng<p->nMaxEqZero ){
    for(i=p->nSample-1; i>=0; i--){
      int j;
      for(j=iChng; j<p->nCol; j++){
        if( p->a[i].anEq[j]==0 ) p->a[i].anEq[j] = p->current.anEq[j];
      }
    }
    p->nMaxEqZero = iChng;
  }
#endif

#if defined(SQLITE_ENABLE_STAT3) && !defined(SQLITE_ENABLE_STAT4)
  if( iChng==0 ){
    tRowcnt nLt = p->current.anLt[0];
    tRowcnt nEq = p->current.anEq[0];

    /* Check if this is to be a periodic sample. If so, add it. */
    if( (nLt/p->nPSample)!=(nLt+nEq)/p->nPSample ){
      p->current.isPSample = 1;
      sampleInsert(p, &p->current, 0);
      p->current.isPSample = 0;
    }else

    /* Or if it is a non-periodic sample. Add it in this case too. */
    if( p->nSample<p->mxSample
     || sampleIsBetter(p, &p->current, &p->a[p->iMin])
    ){
      sampleInsert(p, &p->current, 0);
    }
  }
#endif

#ifndef SQLITE_ENABLE_STAT3_OR_STAT4
  UNUSED_PARAMETER( p );
  UNUSED_PARAMETER( iChng );
#endif
}