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
struct TYPE_8__ {int nTree; int* aTree; TYPE_1__* pTask; TYPE_2__* aReadr; } ;
struct TYPE_7__ {scalar_t__ pFd; int /*<<< orphan*/  nKey; int /*<<< orphan*/  aKey; } ;
struct TYPE_6__ {scalar_t__ pUnpacked; int (* xCompare ) (TYPE_1__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ SortSubtask ;
typedef  TYPE_2__ PmaReader ;
typedef  TYPE_3__ MergeEngine ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int stub1 (TYPE_1__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vdbeMergeEngineCompare(
  MergeEngine *pMerger,  /* Merge engine containing PmaReaders to compare */
  int iOut               /* Store the result in pMerger->aTree[iOut] */
){
  int i1;
  int i2;
  int iRes;
  PmaReader *p1;
  PmaReader *p2;

  assert( iOut<pMerger->nTree && iOut>0 );

  if( iOut>=(pMerger->nTree/2) ){
    i1 = (iOut - pMerger->nTree/2) * 2;
    i2 = i1 + 1;
  }else{
    i1 = pMerger->aTree[iOut*2];
    i2 = pMerger->aTree[iOut*2+1];
  }

  p1 = &pMerger->aReadr[i1];
  p2 = &pMerger->aReadr[i2];

  if( p1->pFd==0 ){
    iRes = i2;
  }else if( p2->pFd==0 ){
    iRes = i1;
  }else{
    SortSubtask *pTask = pMerger->pTask;
    int bCached = 0;
    int res;
    assert( pTask->pUnpacked!=0 );  /* from vdbeSortSubtaskMain() */
    res = pTask->xCompare(
        pTask, &bCached, p1->aKey, p1->nKey, p2->aKey, p2->nKey
    );
    if( res<=0 ){
      iRes = i1;
    }else{
      iRes = i2;
    }
  }

  pMerger->aTree[iOut] = iRes;
}