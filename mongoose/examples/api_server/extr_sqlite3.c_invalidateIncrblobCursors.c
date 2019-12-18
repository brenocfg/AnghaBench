#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i64 ;
struct TYPE_7__ {scalar_t__ nKey; } ;
struct TYPE_10__ {int /*<<< orphan*/  eState; TYPE_1__ info; scalar_t__ isIncrblobHandle; struct TYPE_10__* pNext; } ;
struct TYPE_9__ {TYPE_4__* pCursor; } ;
struct TYPE_8__ {TYPE_3__* pBt; } ;
typedef  TYPE_2__ Btree ;
typedef  TYPE_3__ BtShared ;
typedef  TYPE_4__ BtCursor ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_INVALID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3BtreeHoldsMutex (TYPE_2__*) ; 

__attribute__((used)) static void invalidateIncrblobCursors(
  Btree *pBtree,          /* The database file to check */
  i64 iRow,               /* The rowid that might be changing */
  int isClearTable        /* True if all rows are being deleted */
){
  BtCursor *p;
  BtShared *pBt = pBtree->pBt;
  assert( sqlite3BtreeHoldsMutex(pBtree) );
  for(p=pBt->pCursor; p; p=p->pNext){
    if( p->isIncrblobHandle && (isClearTable || p->info.nKey==iRow) ){
      p->eState = CURSOR_INVALID;
    }
  }
}