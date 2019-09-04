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
struct TYPE_5__ {scalar_t__ iTab; scalar_t__ iSortIdx; scalar_t__ rSetup; int wsFlags; scalar_t__ nSkip; int prereq; scalar_t__ rRun; scalar_t__ nOut; struct TYPE_5__* pNextLoop; } ;
typedef  TYPE_1__ WhereLoop ;

/* Variables and functions */
 int WHERE_AUTO_INDEX ; 
 int WHERE_COLUMN_EQ ; 
 int WHERE_INDEXED ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static WhereLoop **whereLoopFindLesser(
  WhereLoop **ppPrev,
  const WhereLoop *pTemplate
){
  WhereLoop *p;
  for(p=(*ppPrev); p; ppPrev=&p->pNextLoop, p=*ppPrev){
    if( p->iTab!=pTemplate->iTab || p->iSortIdx!=pTemplate->iSortIdx ){
      /* If either the iTab or iSortIdx values for two WhereLoop are different
      ** then those WhereLoops need to be considered separately.  Neither is
      ** a candidate to replace the other. */
      continue;
    }
    /* In the current implementation, the rSetup value is either zero
    ** or the cost of building an automatic index (NlogN) and the NlogN
    ** is the same for compatible WhereLoops. */
    assert( p->rSetup==0 || pTemplate->rSetup==0 
                 || p->rSetup==pTemplate->rSetup );

    /* whereLoopAddBtree() always generates and inserts the automatic index
    ** case first.  Hence compatible candidate WhereLoops never have a larger
    ** rSetup. Call this SETUP-INVARIANT */
    assert( p->rSetup>=pTemplate->rSetup );

    /* Any loop using an appliation-defined index (or PRIMARY KEY or
    ** UNIQUE constraint) with one or more == constraints is better
    ** than an automatic index. Unless it is a skip-scan. */
    if( (p->wsFlags & WHERE_AUTO_INDEX)!=0
     && (pTemplate->nSkip)==0
     && (pTemplate->wsFlags & WHERE_INDEXED)!=0
     && (pTemplate->wsFlags & WHERE_COLUMN_EQ)!=0
     && (p->prereq & pTemplate->prereq)==pTemplate->prereq
    ){
      break;
    }

    /* If existing WhereLoop p is better than pTemplate, pTemplate can be
    ** discarded.  WhereLoop p is better if:
    **   (1)  p has no more dependencies than pTemplate, and
    **   (2)  p has an equal or lower cost than pTemplate
    */
    if( (p->prereq & pTemplate->prereq)==p->prereq    /* (1)  */
     && p->rSetup<=pTemplate->rSetup                  /* (2a) */
     && p->rRun<=pTemplate->rRun                      /* (2b) */
     && p->nOut<=pTemplate->nOut                      /* (2c) */
    ){
      return 0;  /* Discard pTemplate */
    }

    /* If pTemplate is always better than p, then cause p to be overwritten
    ** with pTemplate.  pTemplate is better than p if:
    **   (1)  pTemplate has no more dependences than p, and
    **   (2)  pTemplate has an equal or lower cost than p.
    */
    if( (p->prereq & pTemplate->prereq)==pTemplate->prereq   /* (1)  */
     && p->rRun>=pTemplate->rRun                             /* (2a) */
     && p->nOut>=pTemplate->nOut                             /* (2b) */
    ){
      assert( p->rSetup>=pTemplate->rSetup ); /* SETUP-INVARIANT above */
      break;   /* Cause p to be overwritten by pTemplate */
    }
  }
  return ppPrev;
}