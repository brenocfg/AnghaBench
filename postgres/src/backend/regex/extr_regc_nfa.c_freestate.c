#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct state {scalar_t__ nins; scalar_t__ nouts; struct state* next; struct state* prev; scalar_t__ flag; int /*<<< orphan*/  no; } ;
struct nfa {struct state* free; struct state* states; struct state* slast; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREESTATE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
freestate(struct nfa *nfa,
		  struct state *s)
{
	assert(s != NULL);
	assert(s->nins == 0 && s->nouts == 0);

	s->no = FREESTATE;
	s->flag = 0;
	if (s->next != NULL)
		s->next->prev = s->prev;
	else
	{
		assert(s == nfa->slast);
		nfa->slast = s->prev;
	}
	if (s->prev != NULL)
		s->prev->next = s->next;
	else
	{
		assert(s == nfa->states);
		nfa->states = s->next;
	}
	s->prev = NULL;
	s->next = nfa->free;		/* don't delete it, put it on the free list */
	nfa->free = s;
}