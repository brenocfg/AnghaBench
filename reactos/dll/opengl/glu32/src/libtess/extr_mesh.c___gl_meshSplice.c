#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* anEdge; } ;
struct TYPE_15__ {TYPE_1__* anEdge; } ;
struct TYPE_14__ {TYPE_9__* Lface; TYPE_7__* Org; } ;
typedef  int /*<<< orphan*/  GLUvertex ;
typedef  TYPE_1__ GLUhalfEdge ;
typedef  int /*<<< orphan*/  GLUface ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KillFace (TYPE_9__*,TYPE_9__*) ; 
 int /*<<< orphan*/  KillVertex (TYPE_7__*,TYPE_7__*) ; 
 int /*<<< orphan*/  MakeFace (int /*<<< orphan*/ *,TYPE_1__*,TYPE_9__*) ; 
 int /*<<< orphan*/  MakeVertex (int /*<<< orphan*/ *,TYPE_1__*,TYPE_7__*) ; 
 int /*<<< orphan*/  Splice (TYPE_1__*,TYPE_1__*) ; 
 int TRUE ; 
 int /*<<< orphan*/ * allocFace () ; 
 int /*<<< orphan*/ * allocVertex () ; 

int __gl_meshSplice( GLUhalfEdge *eOrg, GLUhalfEdge *eDst )
{
  int joiningLoops = FALSE;
  int joiningVertices = FALSE;

  if( eOrg == eDst ) return 1;

  if( eDst->Org != eOrg->Org ) {
    /* We are merging two disjoint vertices -- destroy eDst->Org */
    joiningVertices = TRUE;
    KillVertex( eDst->Org, eOrg->Org );
  }
  if( eDst->Lface != eOrg->Lface ) {
    /* We are connecting two disjoint loops -- destroy eDst->Lface */
    joiningLoops = TRUE;
    KillFace( eDst->Lface, eOrg->Lface );
  }

  /* Change the edge structure */
  Splice( eDst, eOrg );

  if( ! joiningVertices ) {
    GLUvertex *newVertex= allocVertex();
    if (newVertex == NULL) return 0;

    /* We split one vertex into two -- the new vertex is eDst->Org.
     * Make sure the old vertex points to a valid half-edge.
     */
    MakeVertex( newVertex, eDst, eOrg->Org );
    eOrg->Org->anEdge = eOrg;
  }
  if( ! joiningLoops ) {
    GLUface *newFace= allocFace();  
    if (newFace == NULL) return 0;

    /* We split one loop into two -- the new loop is eDst->Lface.
     * Make sure the old face points to a valid half-edge.
     */
    MakeFace( newFace, eDst, eOrg->Lface );
    eOrg->Lface->anEdge = eOrg;
  }

  return 1;
}