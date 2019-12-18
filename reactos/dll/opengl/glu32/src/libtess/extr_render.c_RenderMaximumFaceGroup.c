#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct FaceCount {int size; TYPE_2__* eStart; int /*<<< orphan*/  (* render ) (TYPE_1__*,TYPE_2__*,int) ;} ;
struct TYPE_14__ {TYPE_2__* anEdge; } ;
struct TYPE_13__ {struct TYPE_13__* Lprev; struct TYPE_13__* Lnext; } ;
struct TYPE_12__ {int /*<<< orphan*/  flagBoundary; } ;
typedef  TYPE_1__ GLUtesselator ;
typedef  TYPE_2__ GLUhalfEdge ;
typedef  TYPE_3__ GLUface ;

/* Variables and functions */
 struct FaceCount MaximumFan (TYPE_2__*) ; 
 struct FaceCount MaximumStrip (TYPE_2__*) ; 
 int /*<<< orphan*/  RenderTriangle (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,TYPE_2__*,int) ; 

__attribute__((used)) static void RenderMaximumFaceGroup( GLUtesselator *tess, GLUface *fOrig )
{
  /* We want to find the largest triangle fan or strip of unmarked faces
   * which includes the given face fOrig.  There are 3 possible fans
   * passing through fOrig (one centered at each vertex), and 3 possible
   * strips (one for each CCW permutation of the vertices).  Our strategy
   * is to try all of these, and take the primitive which uses the most
   * triangles (a greedy approach).
   */
  GLUhalfEdge *e = fOrig->anEdge;
  struct FaceCount max, newFace;

  max.size = 1;
  max.eStart = e;
  max.render = &RenderTriangle;

  if( ! tess->flagBoundary ) {
    newFace = MaximumFan( e ); if( newFace.size > max.size ) { max = newFace; }
    newFace = MaximumFan( e->Lnext ); if( newFace.size > max.size ) { max = newFace; }
    newFace = MaximumFan( e->Lprev ); if( newFace.size > max.size ) { max = newFace; }

    newFace = MaximumStrip( e ); if( newFace.size > max.size ) { max = newFace; }
    newFace = MaximumStrip( e->Lnext ); if( newFace.size > max.size ) { max = newFace; }
    newFace = MaximumStrip( e->Lprev ); if( newFace.size > max.size ) { max = newFace; }
  }
  (*(max.render))( tess, max.eStart, max.size );
}