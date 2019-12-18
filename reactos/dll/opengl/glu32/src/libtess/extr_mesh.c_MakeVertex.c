#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* Onext; TYPE_1__* Org; } ;
struct TYPE_6__ {int /*<<< orphan*/ * data; TYPE_2__* anEdge; struct TYPE_6__* prev; struct TYPE_6__* next; } ;
typedef  TYPE_1__ GLUvertex ;
typedef  TYPE_2__ GLUhalfEdge ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void MakeVertex( GLUvertex *newVertex, 
			GLUhalfEdge *eOrig, GLUvertex *vNext )
{
  GLUhalfEdge *e;
  GLUvertex *vPrev;
  GLUvertex *vNew = newVertex;

  assert(vNew != NULL);

  /* insert in circular doubly-linked list before vNext */
  vPrev = vNext->prev;
  vNew->prev = vPrev;
  vPrev->next = vNew;
  vNew->next = vNext;
  vNext->prev = vNew;

  vNew->anEdge = eOrig;
  vNew->data = NULL;
  /* leave coords, s, t undefined */

  /* fix other edges on this vertex loop */
  e = eOrig;
  do {
    e->Org = vNew;
    e = e->Onext;
  } while( e != eOrig );
}