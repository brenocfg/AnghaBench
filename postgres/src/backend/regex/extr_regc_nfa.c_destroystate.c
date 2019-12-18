#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct state* next; } ;
struct state {scalar_t__ no; struct state* next; int /*<<< orphan*/ * outs; int /*<<< orphan*/ * ins; TYPE_2__ oas; } ;
struct nfa {TYPE_1__* v; } ;
struct arcbatch {scalar_t__ no; struct arcbatch* next; int /*<<< orphan*/ * outs; int /*<<< orphan*/ * ins; TYPE_2__ oas; } ;
struct TYPE_3__ {int spaceused; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct state*) ; 
 scalar_t__ FREESTATE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
destroystate(struct nfa *nfa,
			 struct state *s)
{
	struct arcbatch *ab;
	struct arcbatch *abnext;

	assert(s->no == FREESTATE);
	for (ab = s->oas.next; ab != NULL; ab = abnext)
	{
		abnext = ab->next;
		FREE(ab);
		nfa->v->spaceused -= sizeof(struct arcbatch);
	}
	s->ins = NULL;
	s->outs = NULL;
	s->next = NULL;
	FREE(s);
	nfa->v->spaceused -= sizeof(struct state);
}