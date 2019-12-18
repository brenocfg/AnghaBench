#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  marked; scalar_t__ inside; struct TYPE_11__* next; } ;
struct TYPE_10__ {TYPE_3__ fHead; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lonelyTriList; } ;
typedef  TYPE_1__ GLUtesselator ;
typedef  TYPE_2__ GLUmesh ;
typedef  TYPE_3__ GLUface ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  RenderLonelyTriangles (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RenderMaximumFaceGroup (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void __gl_renderMesh( GLUtesselator *tess, GLUmesh *mesh )
{
  GLUface *f;

  /* Make a list of separate triangles so we can render them all at once */
  tess->lonelyTriList = NULL;

  for( f = mesh->fHead.next; f != &mesh->fHead; f = f->next ) {
    f->marked = FALSE;
  }
  for( f = mesh->fHead.next; f != &mesh->fHead; f = f->next ) {

    /* We examine all faces in an arbitrary order.  Whenever we find
     * an unprocessed face F, we output a group of faces including F
     * whose size is maximum.
     */
    if( f->inside && ! f->marked ) {
      RenderMaximumFaceGroup( tess, f );
      assert( f->marked );
    }
  }
  if( tess->lonelyTriList != NULL ) {
    RenderLonelyTriangles( tess, tess->lonelyTriList );
    tess->lonelyTriList = NULL;
  }
}