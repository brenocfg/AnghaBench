#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ inTransaction; TYPE_1__* pPage1; int /*<<< orphan*/  pPager; int /*<<< orphan*/  mutex; } ;
struct TYPE_6__ {int aData; } ;
typedef  TYPE_1__ MemPage ;
typedef  TYPE_2__ BtShared ;

/* Variables and functions */
 scalar_t__ TRANS_NONE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ countValidCursors (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  releasePageNotNull (TYPE_1__*) ; 
 int sqlite3PagerRefcount (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unlockBtreeIfUnused(BtShared *pBt){
  assert( sqlite3_mutex_held(pBt->mutex) );
  assert( countValidCursors(pBt,0)==0 || pBt->inTransaction>TRANS_NONE );
  if( pBt->inTransaction==TRANS_NONE && pBt->pPage1!=0 ){
    MemPage *pPage1 = pBt->pPage1;
    assert( pPage1->aData );
    assert( sqlite3PagerRefcount(pBt->pPager)==1 );
    pBt->pPage1 = 0;
    releasePageNotNull(pPage1);
  }
}