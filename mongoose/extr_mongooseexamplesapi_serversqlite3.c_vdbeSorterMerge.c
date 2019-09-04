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
typedef  int /*<<< orphan*/  VdbeCursor ;
struct TYPE_5__ {void* pVal; struct TYPE_5__* pNext; int /*<<< orphan*/  nVal; } ;
typedef  TYPE_1__ SorterRecord ;

/* Variables and functions */
 int /*<<< orphan*/  vdbeSorterCompare (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void vdbeSorterMerge(
  const VdbeCursor *pCsr,         /* For pKeyInfo */
  SorterRecord *p1,               /* First list to merge */
  SorterRecord *p2,               /* Second list to merge */
  SorterRecord **ppOut            /* OUT: Head of merged list */
){
  SorterRecord *pFinal = 0;
  SorterRecord **pp = &pFinal;
  void *pVal2 = p2 ? p2->pVal : 0;

  while( p1 && p2 ){
    int res;
    vdbeSorterCompare(pCsr, 0, p1->pVal, p1->nVal, pVal2, p2->nVal, &res);
    if( res<=0 ){
      *pp = p1;
      pp = &p1->pNext;
      p1 = p1->pNext;
      pVal2 = 0;
    }else{
      *pp = p2;
       pp = &p2->pNext;
      p2 = p2->pNext;
      if( p2==0 ) break;
      pVal2 = p2->pVal;
    }
  }
  *pp = p1 ? p1 : p2;
  *ppOut = pFinal;
}