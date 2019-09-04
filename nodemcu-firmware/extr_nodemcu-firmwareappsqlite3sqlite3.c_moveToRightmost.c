#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ nSize; } ;
struct TYPE_9__ {scalar_t__ eState; size_t iPage; int curFlags; TYPE_1__ info; scalar_t__ ix; TYPE_2__** apPage; } ;
struct TYPE_8__ {int hdrOffset; scalar_t__ nCell; int /*<<< orphan*/ * aData; int /*<<< orphan*/  leaf; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  TYPE_2__ MemPage ;
typedef  TYPE_3__ BtCursor ;

/* Variables and functions */
 int BTCF_ValidNKey ; 
 scalar_t__ CURSOR_VALID ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int cursorOwnsBtShared (TYPE_3__*) ; 
 int /*<<< orphan*/  get4byte (int /*<<< orphan*/ *) ; 
 int moveToChild (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int moveToRightmost(BtCursor *pCur){
  Pgno pgno;
  int rc = SQLITE_OK;
  MemPage *pPage = 0;

  assert( cursorOwnsBtShared(pCur) );
  assert( pCur->eState==CURSOR_VALID );
  while( !(pPage = pCur->apPage[pCur->iPage])->leaf ){
    pgno = get4byte(&pPage->aData[pPage->hdrOffset+8]);
    pCur->ix = pPage->nCell;
    rc = moveToChild(pCur, pgno);
    if( rc ) return rc;
  }
  pCur->ix = pPage->nCell-1;
  assert( pCur->info.nSize==0 );
  assert( (pCur->curFlags & BTCF_ValidNKey)==0 );
  return SQLITE_OK;
}