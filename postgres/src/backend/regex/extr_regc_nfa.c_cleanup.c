#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct state {int /*<<< orphan*/  no; struct state* next; int /*<<< orphan*/  flag; TYPE_1__* tmp; } ;
struct nfa {int nstates; struct state* states; TYPE_1__* post; int /*<<< orphan*/  pre; } ;
struct TYPE_3__ {scalar_t__ nins; struct TYPE_3__* tmp; } ;

/* Variables and functions */
 scalar_t__ NISERR () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cleartraverse (struct nfa*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dropstate (struct nfa*,struct state*) ; 
 int /*<<< orphan*/  markcanreach (struct nfa*,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  markreachable (struct nfa*,int /*<<< orphan*/ ,struct state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cleanup(struct nfa *nfa)
{
	struct state *s;
	struct state *nexts;
	int			n;

	if (NISERR())
		return;

	/* clear out unreachable or dead-end states */
	/* use pre to mark reachable, then post to mark can-reach-post */
	markreachable(nfa, nfa->pre, (struct state *) NULL, nfa->pre);
	markcanreach(nfa, nfa->post, nfa->pre, nfa->post);
	for (s = nfa->states; s != NULL && !NISERR(); s = nexts)
	{
		nexts = s->next;
		if (s->tmp != nfa->post && !s->flag)
			dropstate(nfa, s);
	}
	assert(NISERR() || nfa->post->nins == 0 || nfa->post->tmp == nfa->post);
	cleartraverse(nfa, nfa->pre);
	assert(NISERR() || nfa->post->nins == 0 || nfa->post->tmp == NULL);
	/* the nins==0 (final unreachable) case will be caught later */

	/* renumber surviving states */
	n = 0;
	for (s = nfa->states; s != NULL; s = s->next)
		s->no = n++;
	nfa->nstates = n;
}