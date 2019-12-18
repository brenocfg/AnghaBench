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
struct state {struct state* next; scalar_t__ nouts; scalar_t__ nins; } ;
struct nfa {int nstates; int /*<<< orphan*/ * post; int /*<<< orphan*/ * pre; int /*<<< orphan*/ * slast; struct state* free; struct state* states; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct nfa*) ; 
 int /*<<< orphan*/  destroystate (struct nfa*,struct state*) ; 
 int /*<<< orphan*/  freestate (struct nfa*,struct state*) ; 

__attribute__((used)) static void
freenfa(struct nfa *nfa)
{
	struct state *s;

	while ((s = nfa->states) != NULL)
	{
		s->nins = s->nouts = 0; /* don't worry about arcs */
		freestate(nfa, s);
	}
	while ((s = nfa->free) != NULL)
	{
		nfa->free = s->next;
		destroystate(nfa, s);
	}

	nfa->slast = NULL;
	nfa->nstates = -1;
	nfa->pre = NULL;
	nfa->post = NULL;
	FREE(nfa);
}