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
struct TYPE_8__ {scalar_t__ nKey; } ;
struct TYPE_10__ {int curFlags; scalar_t__ pgnoRoot; int /*<<< orphan*/  eState; TYPE_2__ info; struct TYPE_10__* pNext; } ;
struct TYPE_9__ {int hasIncrblobCur; TYPE_1__* pBt; } ;
struct TYPE_7__ {TYPE_4__* pCursor; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_3__ Btree ;
typedef  TYPE_4__ BtCursor ;

/* Variables and functions */
 int BTCF_Incrblob ; 
 int /*<<< orphan*/  CURSOR_INVALID ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3BtreeHoldsMutex (TYPE_3__*) ; 

__attribute__((used)) static void invalidateIncrblobCursors(
  Btree *pBtree,          /* The database file to check */
  Pgno pgnoRoot,          /* The table that might be changing */
  i64 iRow,               /* The rowid that might be changing */
  int isClearTable        /* True if all rows are being deleted */
){
  BtCursor *p;
  if( pBtree->hasIncrblobCur==0 ) return;
  assert( sqlite3BtreeHoldsMutex(pBtree) );
  pBtree->hasIncrblobCur = 0;
  for(p=pBtree->pBt->pCursor; p; p=p->pNext){
    if( (p->curFlags & BTCF_Incrblob)!=0 ){
      pBtree->hasIncrblobCur = 1;
      if( p->pgnoRoot==pgnoRoot && (isClearTable || p->info.nKey==iRow) ){
        p->eState = CURSOR_INVALID;
      }
    }
  }
}