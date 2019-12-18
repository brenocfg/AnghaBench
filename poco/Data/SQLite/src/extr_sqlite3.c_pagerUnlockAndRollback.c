#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ eState; int /*<<< orphan*/  exclusiveMode; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ PAGER_ERROR ; 
 scalar_t__ PAGER_OPEN ; 
 scalar_t__ PAGER_READER ; 
 scalar_t__ PAGER_WRITER_LOCKED ; 
 int /*<<< orphan*/  assert (int) ; 
 int assert_pager_state (TYPE_1__*) ; 
 int /*<<< orphan*/  pager_end_transaction (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pager_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3BeginBenignMalloc () ; 
 int /*<<< orphan*/  sqlite3EndBenignMalloc () ; 
 int /*<<< orphan*/  sqlite3PagerRollback (TYPE_1__*) ; 

__attribute__((used)) static void pagerUnlockAndRollback(Pager *pPager){
  if( pPager->eState!=PAGER_ERROR && pPager->eState!=PAGER_OPEN ){
    assert( assert_pager_state(pPager) );
    if( pPager->eState>=PAGER_WRITER_LOCKED ){
      sqlite3BeginBenignMalloc();
      sqlite3PagerRollback(pPager);
      sqlite3EndBenignMalloc();
    }else if( !pPager->exclusiveMode ){
      assert( pPager->eState==PAGER_READER );
      pager_end_transaction(pPager, 0, 0);
    }
  }
  pager_unlock(pPager);
}