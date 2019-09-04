#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct RowSetEntry {int dummy; } ;
struct RowSetChunk {int /*<<< orphan*/  aEntry; struct RowSetChunk* pNextChunk; } ;
struct TYPE_3__ {scalar_t__ nFresh; int /*<<< orphan*/  pFresh; struct RowSetChunk* pChunk; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ RowSet ;

/* Variables and functions */
 scalar_t__ ROWSET_ENTRY_PER_CHUNK ; 
 int /*<<< orphan*/  assert (int) ; 
 struct RowSetChunk* sqlite3DbMallocRawNN (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct RowSetEntry *rowSetEntryAlloc(RowSet *p){
  assert( p!=0 );
  if( p->nFresh==0 ){  /*OPTIMIZATION-IF-FALSE*/
    /* We could allocate a fresh RowSetEntry each time one is needed, but it
    ** is more efficient to pull a preallocated entry from the pool */
    struct RowSetChunk *pNew;
    pNew = sqlite3DbMallocRawNN(p->db, sizeof(*pNew));
    if( pNew==0 ){
      return 0;
    }
    pNew->pNextChunk = p->pChunk;
    p->pChunk = pNew;
    p->pFresh = pNew->aEntry;
    p->nFresh = ROWSET_ENTRY_PER_CHUNK;
  }
  p->nFresh--;
  return p->pFresh++;
}