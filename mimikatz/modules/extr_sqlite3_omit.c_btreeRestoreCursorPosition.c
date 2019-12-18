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
struct TYPE_5__ {scalar_t__ eState; int skipNext; scalar_t__ pKey; int /*<<< orphan*/  nKey; } ;
typedef  TYPE_1__ BtCursor ;

/* Variables and functions */
 scalar_t__ CURSOR_FAULT ; 
 scalar_t__ CURSOR_INVALID ; 
 scalar_t__ CURSOR_REQUIRESEEK ; 
 scalar_t__ CURSOR_SKIPNEXT ; 
 scalar_t__ CURSOR_VALID ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int btreeMoveto (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int cursorOwnsBtShared (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 

__attribute__((used)) static int btreeRestoreCursorPosition(BtCursor *pCur){
  int rc;
  int skipNext;
  assert( cursorOwnsBtShared(pCur) );
  assert( pCur->eState>=CURSOR_REQUIRESEEK );
  if( pCur->eState==CURSOR_FAULT ){
    return pCur->skipNext;
  }
  pCur->eState = CURSOR_INVALID;
  rc = btreeMoveto(pCur, pCur->pKey, pCur->nKey, 0, &skipNext);
  if( rc==SQLITE_OK ){
    sqlite3_free(pCur->pKey);
    pCur->pKey = 0;
    assert( pCur->eState==CURSOR_VALID || pCur->eState==CURSOR_INVALID );
    if( skipNext ) pCur->skipNext = skipNext;
    if( pCur->skipNext && pCur->eState==CURSOR_VALID ){
      pCur->eState = CURSOR_SKIPNEXT;
    }
  }
  return rc;
}