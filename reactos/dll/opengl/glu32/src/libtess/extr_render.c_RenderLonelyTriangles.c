#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* anEdge; struct TYPE_12__* trail; } ;
struct TYPE_11__ {struct TYPE_11__* Lnext; TYPE_2__* Org; TYPE_1__* Rface; } ;
struct TYPE_10__ {scalar_t__ flagBoundary; } ;
struct TYPE_9__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  inside; } ;
typedef  TYPE_3__ GLUtesselator ;
typedef  TYPE_4__ GLUhalfEdge ;
typedef  TYPE_5__ GLUface ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_BEGIN_OR_BEGIN_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CALL_EDGE_FLAG_OR_EDGE_FLAG_DATA (int) ; 
 int /*<<< orphan*/  CALL_END_OR_END_DATA () ; 
 int /*<<< orphan*/  CALL_VERTEX_OR_VERTEX_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_TRIANGLES ; 

__attribute__((used)) static void RenderLonelyTriangles( GLUtesselator *tess, GLUface *f )
{
  /* Now we render all the separate triangles which could not be
   * grouped into a triangle fan or strip.
   */
  GLUhalfEdge *e;
  int newState;
  int edgeState = -1;	/* force edge state output for first vertex */

  CALL_BEGIN_OR_BEGIN_DATA( GL_TRIANGLES );

  for( ; f != NULL; f = f->trail ) {
    /* Loop once for each edge (there will always be 3 edges) */

    e = f->anEdge;
    do {
      if( tess->flagBoundary ) {
	/* Set the "edge state" to TRUE just before we output the
	 * first vertex of each edge on the polygon boundary.
	 */
	newState = ! e->Rface->inside;
	if( edgeState != newState ) {
	  edgeState = newState;
          CALL_EDGE_FLAG_OR_EDGE_FLAG_DATA( edgeState );
	}
      }
      CALL_VERTEX_OR_VERTEX_DATA( e->Org->data );

      e = e->Lnext;
    } while( e != f->anEdge );
  }
  CALL_END_OR_END_DATA();
}