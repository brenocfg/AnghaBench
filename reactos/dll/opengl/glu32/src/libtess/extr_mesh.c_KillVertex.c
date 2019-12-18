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
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* prev; TYPE_2__* anEdge; } ;
typedef  TYPE_1__ GLUvertex ;
typedef  TYPE_2__ GLUhalfEdge ;

/* Variables and functions */
 int /*<<< orphan*/  memFree (TYPE_1__*) ; 

__attribute__((used)) static void KillVertex( GLUvertex *vDel, GLUvertex *newOrg )
{
  GLUhalfEdge *e, *eStart = vDel->anEdge;
  GLUvertex *vPrev, *vNext;

  /* change the origin of all affected edges */
  e = eStart;
  do {
    e->Org = newOrg;
    e = e->Onext;
  } while( e != eStart );

  /* delete from circular doubly-linked list */
  vPrev = vDel->prev;
  vNext = vDel->next;
  vNext->prev = vPrev;
  vPrev->next = vNext;

  memFree( vDel );
}