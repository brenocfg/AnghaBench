#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int tnum; scalar_t__ pSchema; TYPE_3__* pIndex; } ;
typedef  TYPE_1__ Table ;
struct TYPE_11__ {int nDb; } ;
struct TYPE_10__ {int tnum; scalar_t__ pSchema; struct TYPE_10__* pNext; } ;
struct TYPE_9__ {TYPE_4__* db; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ Index ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  destroyRootPage (TYPE_2__*,int,int) ; 
 int sqlite3SchemaToIndex (TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static void destroyTable(Parse *pParse, Table *pTab){
  /* If the database may be auto-vacuum capable (if SQLITE_OMIT_AUTOVACUUM
  ** is not defined), then it is important to call OP_Destroy on the
  ** table and index root-pages in order, starting with the numerically 
  ** largest root-page number. This guarantees that none of the root-pages
  ** to be destroyed is relocated by an earlier OP_Destroy. i.e. if the
  ** following were coded:
  **
  ** OP_Destroy 4 0
  ** ...
  ** OP_Destroy 5 0
  **
  ** and root page 5 happened to be the largest root-page number in the
  ** database, then root page 5 would be moved to page 4 by the 
  ** "OP_Destroy 4 0" opcode. The subsequent "OP_Destroy 5 0" would hit
  ** a free-list page.
  */
  int iTab = pTab->tnum;
  int iDestroyed = 0;

  while( 1 ){
    Index *pIdx;
    int iLargest = 0;

    if( iDestroyed==0 || iTab<iDestroyed ){
      iLargest = iTab;
    }
    for(pIdx=pTab->pIndex; pIdx; pIdx=pIdx->pNext){
      int iIdx = pIdx->tnum;
      assert( pIdx->pSchema==pTab->pSchema );
      if( (iDestroyed==0 || (iIdx<iDestroyed)) && iIdx>iLargest ){
        iLargest = iIdx;
      }
    }
    if( iLargest==0 ){
      return;
    }else{
      int iDb = sqlite3SchemaToIndex(pParse->db, pTab->pSchema);
      assert( iDb>=0 && iDb<pParse->db->nDb );
      destroyRootPage(pParse, iLargest, iDb);
      iDestroyed = iLargest;
    }
  }
}