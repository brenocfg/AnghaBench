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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {scalar_t__ nSize; } ;
struct TYPE_7__ {scalar_t__ eState; int iPage; int curFlags; int /*<<< orphan*/  curPagerFlags; int /*<<< orphan*/ * apPage; scalar_t__ ix; scalar_t__* aiIdx; TYPE_1__ info; int /*<<< orphan*/ * pBt; } ;
typedef  int /*<<< orphan*/  BtShared ;
typedef  TYPE_2__ BtCursor ;

/* Variables and functions */
 int BTCF_ValidNKey ; 
 int BTCF_ValidOvfl ; 
 int BTCURSOR_MAX_DEPTH ; 
 scalar_t__ CURSOR_VALID ; 
 int SQLITE_CORRUPT_BKPT ; 
 int /*<<< orphan*/  assert (int) ; 
 int cursorOwnsBtShared (TYPE_2__*) ; 
 int getAndInitPage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int moveToChild(BtCursor *pCur, u32 newPgno){
  BtShared *pBt = pCur->pBt;

  assert( cursorOwnsBtShared(pCur) );
  assert( pCur->eState==CURSOR_VALID );
  assert( pCur->iPage<BTCURSOR_MAX_DEPTH );
  assert( pCur->iPage>=0 );
  if( pCur->iPage>=(BTCURSOR_MAX_DEPTH-1) ){
    return SQLITE_CORRUPT_BKPT;
  }
  pCur->info.nSize = 0;
  pCur->curFlags &= ~(BTCF_ValidNKey|BTCF_ValidOvfl);
  pCur->aiIdx[pCur->iPage++] = pCur->ix;
  pCur->ix = 0;
  return getAndInitPage(pBt, newPgno, &pCur->apPage[pCur->iPage],
                        pCur, pCur->curPagerFlags);
}