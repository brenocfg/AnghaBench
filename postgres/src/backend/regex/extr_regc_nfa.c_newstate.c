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
struct TYPE_4__ {int /*<<< orphan*/ * next; } ;
struct state {struct state* prev; struct state* next; int /*<<< orphan*/ * tmp; int /*<<< orphan*/ * outs; scalar_t__ nouts; int /*<<< orphan*/ * ins; scalar_t__ nins; scalar_t__ flag; scalar_t__ no; scalar_t__ noas; int /*<<< orphan*/ * free; TYPE_2__ oas; } ;
struct nfa {scalar_t__ nstates; struct state* slast; struct state* states; TYPE_1__* v; struct state* free; } ;
struct TYPE_3__ {scalar_t__ spaceused; int /*<<< orphan*/  re; } ;

/* Variables and functions */
 scalar_t__ CANCEL_REQUESTED (int /*<<< orphan*/ ) ; 
 scalar_t__ MALLOC (int) ; 
 int /*<<< orphan*/  NERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_CANCEL ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  REG_ETOOBIG ; 
 scalar_t__ REG_MAX_COMPILE_SPACE ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static struct state *			/* NULL on error */
newstate(struct nfa *nfa)
{
	struct state *s;

	/*
	 * This is a handy place to check for operation cancel during regex
	 * compilation, since no code path will go very long without making a new
	 * state or arc.
	 */
	if (CANCEL_REQUESTED(nfa->v->re))
	{
		NERR(REG_CANCEL);
		return NULL;
	}

	if (nfa->free != NULL)
	{
		s = nfa->free;
		nfa->free = s->next;
	}
	else
	{
		if (nfa->v->spaceused >= REG_MAX_COMPILE_SPACE)
		{
			NERR(REG_ETOOBIG);
			return NULL;
		}
		s = (struct state *) MALLOC(sizeof(struct state));
		if (s == NULL)
		{
			NERR(REG_ESPACE);
			return NULL;
		}
		nfa->v->spaceused += sizeof(struct state);
		s->oas.next = NULL;
		s->free = NULL;
		s->noas = 0;
	}

	assert(nfa->nstates >= 0);
	s->no = nfa->nstates++;
	s->flag = 0;
	if (nfa->states == NULL)
		nfa->states = s;
	s->nins = 0;
	s->ins = NULL;
	s->nouts = 0;
	s->outs = NULL;
	s->tmp = NULL;
	s->next = NULL;
	if (nfa->slast != NULL)
	{
		assert(nfa->slast->next == NULL);
		nfa->slast->next = s;
	}
	s->prev = nfa->slast;
	nfa->slast = s;
	return s;
}