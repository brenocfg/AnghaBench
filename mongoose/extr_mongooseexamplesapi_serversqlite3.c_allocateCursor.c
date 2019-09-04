#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {int iDb; int nField; int /*<<< orphan*/ * pCursor; int /*<<< orphan*/ * aType; } ;
typedef  TYPE_1__ VdbeCursor ;
struct TYPE_11__ {int nMem; int nCursor; TYPE_1__** apCsr; TYPE_3__* aMem; } ;
typedef  TYPE_2__ Vdbe ;
struct TYPE_12__ {int /*<<< orphan*/ * z; } ;
typedef  TYPE_3__ Mem ;
typedef  int /*<<< orphan*/  BtCursor ;

/* Variables and functions */
 int ROUND8 (int) ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int sqlite3BtreeCursorSize () ; 
 int /*<<< orphan*/  sqlite3BtreeCursorZero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3VdbeFreeCursor (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ sqlite3VdbeMemGrow (TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VdbeCursor *allocateCursor(
  Vdbe *p,              /* The virtual machine */
  int iCur,             /* Index of the new VdbeCursor */
  int nField,           /* Number of fields in the table or index */
  int iDb,              /* Database the cursor belongs to, or -1 */
  int isBtreeCursor     /* True for B-Tree.  False for pseudo-table or vtab */
){
  /* Find the memory cell that will be used to store the blob of memory
  ** required for this VdbeCursor structure. It is convenient to use a 
  ** vdbe memory cell to manage the memory allocation required for a
  ** VdbeCursor structure for the following reasons:
  **
  **   * Sometimes cursor numbers are used for a couple of different
  **     purposes in a vdbe program. The different uses might require
  **     different sized allocations. Memory cells provide growable
  **     allocations.
  **
  **   * When using ENABLE_MEMORY_MANAGEMENT, memory cell buffers can
  **     be freed lazily via the sqlite3_release_memory() API. This
  **     minimizes the number of malloc calls made by the system.
  **
  ** Memory cells for cursors are allocated at the top of the address
  ** space. Memory cell (p->nMem) corresponds to cursor 0. Space for
  ** cursor 1 is managed by memory cell (p->nMem-1), etc.
  */
  Mem *pMem = &p->aMem[p->nMem-iCur];

  int nByte;
  VdbeCursor *pCx = 0;
  nByte = 
      ROUND8(sizeof(VdbeCursor)) + 
      (isBtreeCursor?sqlite3BtreeCursorSize():0) + 
      2*nField*sizeof(u32);

  assert( iCur<p->nCursor );
  if( p->apCsr[iCur] ){
    sqlite3VdbeFreeCursor(p, p->apCsr[iCur]);
    p->apCsr[iCur] = 0;
  }
  if( SQLITE_OK==sqlite3VdbeMemGrow(pMem, nByte, 0) ){
    p->apCsr[iCur] = pCx = (VdbeCursor*)pMem->z;
    memset(pCx, 0, sizeof(VdbeCursor));
    pCx->iDb = iDb;
    pCx->nField = nField;
    if( nField ){
      pCx->aType = (u32 *)&pMem->z[ROUND8(sizeof(VdbeCursor))];
    }
    if( isBtreeCursor ){
      pCx->pCursor = (BtCursor*)
          &pMem->z[ROUND8(sizeof(VdbeCursor))+2*nField*sizeof(u32)];
      sqlite3BtreeCursorZero(pCx->pCursor);
    }
  }
  return pCx;
}