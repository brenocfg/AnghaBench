#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; struct TYPE_4__* Sym; } ;
typedef  TYPE_1__ GLUhalfEdge ;

/* Variables and functions */
 int /*<<< orphan*/  memFree (TYPE_1__*) ; 

__attribute__((used)) static void KillEdge( GLUhalfEdge *eDel )
{
  GLUhalfEdge *ePrev, *eNext;

  /* Half-edges are allocated in pairs, see EdgePair above */
  if( eDel->Sym < eDel ) { eDel = eDel->Sym; }

  /* delete from circular doubly-linked list */
  eNext = eDel->next;
  ePrev = eDel->Sym->next;
  eNext->Sym->next = ePrev;
  ePrev->Sym->next = eNext;

  memFree( eDel );
}