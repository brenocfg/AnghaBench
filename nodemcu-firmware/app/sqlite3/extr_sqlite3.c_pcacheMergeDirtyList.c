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
struct TYPE_5__ {scalar_t__ pgno; struct TYPE_5__* pDirty; } ;
typedef  TYPE_1__ PgHdr ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static PgHdr *pcacheMergeDirtyList(PgHdr *pA, PgHdr *pB){
  PgHdr result, *pTail;
  pTail = &result;
  assert( pA!=0 && pB!=0 );
  for(;;){
    if( pA->pgno<pB->pgno ){
      pTail->pDirty = pA;
      pTail = pA;
      pA = pA->pDirty;
      if( pA==0 ){
        pTail->pDirty = pB;
        break;
      }
    }else{
      pTail->pDirty = pB;
      pTail = pB;
      pB = pB->pDirty;
      if( pB==0 ){
        pTail->pDirty = pA;
        break;
      }
    }
  }
  return result.pDirty;
}