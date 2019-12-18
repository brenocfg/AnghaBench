#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* pParent; } ;
typedef  TYPE_1__ VdbeFrame ;
struct TYPE_8__ {scalar_t__ nFrame; scalar_t__ pAuxData; int /*<<< orphan*/  db; TYPE_1__* pDelFrame; int /*<<< orphan*/  nMem; scalar_t__ aMem; TYPE_1__* pFrame; } ;
typedef  TYPE_2__ Vdbe ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  closeCursorsInFrame (TYPE_2__*) ; 
 int /*<<< orphan*/  releaseMemArray (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeDeleteAuxData (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeFrameDelete (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VdbeFrameRestore (TYPE_1__*) ; 

__attribute__((used)) static void closeAllCursors(Vdbe *p){
  if( p->pFrame ){
    VdbeFrame *pFrame;
    for(pFrame=p->pFrame; pFrame->pParent; pFrame=pFrame->pParent);
    sqlite3VdbeFrameRestore(pFrame);
    p->pFrame = 0;
    p->nFrame = 0;
  }
  assert( p->nFrame==0 );
  closeCursorsInFrame(p);
  if( p->aMem ){
    releaseMemArray(p->aMem, p->nMem);
  }
  while( p->pDelFrame ){
    VdbeFrame *pDel = p->pDelFrame;
    p->pDelFrame = pDel->pParent;
    sqlite3VdbeFrameDelete(pDel);
  }

  /* Delete any auxdata allocations made by the VM */
  if( p->pAuxData ) sqlite3VdbeDeleteAuxData(p->db, &p->pAuxData, -1, 0);
  assert( p->pAuxData==0 );
}