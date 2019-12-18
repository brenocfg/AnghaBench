#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int (* xCompare ) (TYPE_3__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {TYPE_2__* pNext; } ;
struct TYPE_11__ {TYPE_1__ u; int /*<<< orphan*/  nVal; } ;
typedef  TYPE_2__ SorterRecord ;
typedef  TYPE_3__ SortSubtask ;

/* Variables and functions */
 int /*<<< orphan*/  SRVAL (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int stub1 (TYPE_3__*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SorterRecord *vdbeSorterMerge(
  SortSubtask *pTask,             /* Calling thread context */
  SorterRecord *p1,               /* First list to merge */
  SorterRecord *p2                /* Second list to merge */
){
  SorterRecord *pFinal = 0;
  SorterRecord **pp = &pFinal;
  int bCached = 0;

  assert( p1!=0 && p2!=0 );
  for(;;){
    int res;
    res = pTask->xCompare(
        pTask, &bCached, SRVAL(p1), p1->nVal, SRVAL(p2), p2->nVal
    );

    if( res<=0 ){
      *pp = p1;
      pp = &p1->u.pNext;
      p1 = p1->u.pNext;
      if( p1==0 ){
        *pp = p2;
        break;
      }
    }else{
      *pp = p2;
      pp = &p2->u.pNext;
      p2 = p2->u.pNext;
      bCached = 0;
      if( p2==0 ){
        *pp = p1;
        break;
      }
    }
  }
  return pFinal;
}