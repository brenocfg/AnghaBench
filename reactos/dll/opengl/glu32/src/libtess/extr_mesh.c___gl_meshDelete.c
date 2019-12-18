#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* anEdge; } ;
struct TYPE_11__ {int /*<<< orphan*/  anEdge; } ;
struct TYPE_10__ {int /*<<< orphan*/  Oprev; struct TYPE_10__* Onext; TYPE_6__* Org; TYPE_5__* Lface; TYPE_5__* Rface; struct TYPE_10__* Sym; } ;
typedef  TYPE_1__ GLUhalfEdge ;
typedef  int /*<<< orphan*/  GLUface ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KillEdge (TYPE_1__*) ; 
 int /*<<< orphan*/  KillFace (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  KillVertex (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MakeFace (int /*<<< orphan*/ *,TYPE_1__*,TYPE_5__*) ; 
 int /*<<< orphan*/  Splice (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/ * allocFace () ; 

int __gl_meshDelete( GLUhalfEdge *eDel )
{
  GLUhalfEdge *eDelSym = eDel->Sym;
  int joiningLoops = FALSE;

  /* First step: disconnect the origin vertex eDel->Org.  We make all
   * changes to get a consistent mesh in this "intermediate" state.
   */
  if( eDel->Lface != eDel->Rface ) {
    /* We are joining two loops into one -- remove the left face */
    joiningLoops = TRUE;
    KillFace( eDel->Lface, eDel->Rface );
  }

  if( eDel->Onext == eDel ) {
    KillVertex( eDel->Org, NULL );
  } else {
    /* Make sure that eDel->Org and eDel->Rface point to valid half-edges */
    eDel->Rface->anEdge = eDel->Oprev;
    eDel->Org->anEdge = eDel->Onext;

    Splice( eDel, eDel->Oprev );
    if( ! joiningLoops ) {
      GLUface *newFace= allocFace();
      if (newFace == NULL) return 0; 

      /* We are splitting one loop into two -- create a new loop for eDel. */
      MakeFace( newFace, eDel, eDel->Lface );
    }
  }

  /* Claim: the mesh is now in a consistent state, except that eDel->Org
   * may have been deleted.  Now we disconnect eDel->Dst.
   */
  if( eDelSym->Onext == eDelSym ) {
    KillVertex( eDelSym->Org, NULL );
    KillFace( eDelSym->Lface, NULL );
  } else {
    /* Make sure that eDel->Dst and eDel->Lface point to valid half-edges */
    eDel->Lface->anEdge = eDelSym->Oprev;
    eDelSym->Org->anEdge = eDelSym->Onext;
    Splice( eDelSym, eDelSym->Oprev );
  }

  /* Any isolated vertices or faces have already been freed. */
  KillEdge( eDel );

  return 1;
}