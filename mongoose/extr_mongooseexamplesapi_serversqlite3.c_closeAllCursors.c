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
typedef  int /*<<< orphan*/  VdbeCursor ;
struct TYPE_8__ {int nCursor; TYPE_1__* pDelFrame; int /*<<< orphan*/  nMem; int /*<<< orphan*/ * aMem; int /*<<< orphan*/ ** apCsr; scalar_t__ nFrame; TYPE_1__* pFrame; } ;
typedef  TYPE_2__ Vdbe ;

/* Variables and functions */
 int /*<<< orphan*/  releaseMemArray (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeFrameDelete (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VdbeFrameRestore (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3VdbeFreeCursor (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void closeAllCursors(Vdbe *p){
  if( p->pFrame ){
    VdbeFrame *pFrame;
    for(pFrame=p->pFrame; pFrame->pParent; pFrame=pFrame->pParent);
    sqlite3VdbeFrameRestore(pFrame);
  }
  p->pFrame = 0;
  p->nFrame = 0;

  if( p->apCsr ){
    int i;
    for(i=0; i<p->nCursor; i++){
      VdbeCursor *pC = p->apCsr[i];
      if( pC ){
        sqlite3VdbeFreeCursor(p, pC);
        p->apCsr[i] = 0;
      }
    }
  }
  if( p->aMem ){
    releaseMemArray(&p->aMem[1], p->nMem);
  }
  while( p->pDelFrame ){
    VdbeFrame *pDel = p->pDelFrame;
    p->pDelFrame = pDel->pParent;
    sqlite3VdbeFrameDelete(pDel);
  }
}