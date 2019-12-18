#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {scalar_t__ fixUpperEdge; TYPE_3__* eUp; } ;
struct TYPE_30__ {struct TYPE_30__* Onext; struct TYPE_30__* Oprev; struct TYPE_30__* Sym; int /*<<< orphan*/  Dst; int /*<<< orphan*/  Org; } ;
struct TYPE_29__ {int /*<<< orphan*/  env; } ;
struct TYPE_28__ {int /*<<< orphan*/  anEdge; } ;
typedef  TYPE_1__ GLUvertex ;
typedef  TYPE_2__ GLUtesselator ;
typedef  TYPE_3__ GLUhalfEdge ;
typedef  TYPE_4__ ActiveRegion ;

/* Variables and functions */
 int /*<<< orphan*/  AddRightEdges (TYPE_2__*,TYPE_4__*,TYPE_3__*,TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteRegion (TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  EdgeGoesLeft (TYPE_3__*) ; 
 scalar_t__ FALSE ; 
 TYPE_4__* RegionBelow (TYPE_4__*) ; 
 int /*<<< orphan*/  SpliceMergeVertices (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SweepEvent (TYPE_2__*,TYPE_1__*) ; 
 int TOLERANCE_NONZERO ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__* TopRightRegion (TYPE_4__*) ; 
 scalar_t__ VertEq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  __gl_meshDelete (TYPE_3__*) ; 
 int /*<<< orphan*/  __gl_meshSplice (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * __gl_meshSplitEdge (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ConnectLeftDegenerate( GLUtesselator *tess,
				   ActiveRegion *regUp, GLUvertex *vEvent )
/*
 * The event vertex lies exacty on an already-processed edge or vertex.
 * Adding the new vertex involves splicing it into the already-processed
 * part of the mesh.
 */
{
  GLUhalfEdge *e, *eTopLeft, *eTopRight, *eLast;
  ActiveRegion *reg;

  e = regUp->eUp;
  if( VertEq( e->Org, vEvent )) {
    /* e->Org is an unprocessed vertex - just combine them, and wait
     * for e->Org to be pulled from the queue
     */
    assert( TOLERANCE_NONZERO );
    SpliceMergeVertices( tess, e, vEvent->anEdge );
    return;
  }

  if( ! VertEq( e->Dst, vEvent )) {
    /* General case -- splice vEvent into edge e which passes through it */
    if (__gl_meshSplitEdge( e->Sym ) == NULL) longjmp(tess->env,1);
    if( regUp->fixUpperEdge ) {
      /* This edge was fixable -- delete unused portion of original edge */
      if ( !__gl_meshDelete( e->Onext ) ) longjmp(tess->env,1);
      regUp->fixUpperEdge = FALSE;
    }
    if ( !__gl_meshSplice( vEvent->anEdge, e ) ) longjmp(tess->env,1);
    SweepEvent( tess, vEvent ); /* recurse */
    return;
  }

  /* vEvent coincides with e->Dst, which has already been processed.
   * Splice in the additional right-going edges.
   */
  assert( TOLERANCE_NONZERO );
  regUp = TopRightRegion( regUp );
  reg = RegionBelow( regUp );
  eTopRight = reg->eUp->Sym;
  eTopLeft = eLast = eTopRight->Onext;
  if( reg->fixUpperEdge ) {
    /* Here e->Dst has only a single fixable edge going right.
     * We can delete it since now we have some real right-going edges.
     */
    assert( eTopLeft != eTopRight );   /* there are some left edges too */
    DeleteRegion( tess, reg );
    if ( !__gl_meshDelete( eTopRight ) ) longjmp(tess->env,1);
    eTopRight = eTopLeft->Oprev;
  }
  if ( !__gl_meshSplice( vEvent->anEdge, eTopRight ) ) longjmp(tess->env,1);
  if( ! EdgeGoesLeft( eTopLeft )) {
    /* e->Dst had no left-going edges -- indicate this to AddRightEdges() */
    eTopLeft = NULL;
  }
  AddRightEdges( tess, regUp, eTopRight->Onext, eLast, eTopLeft, TRUE );
}