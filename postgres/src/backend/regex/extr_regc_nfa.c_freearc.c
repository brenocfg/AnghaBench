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
struct state {struct arc* free; int /*<<< orphan*/  nins; struct arc* ins; int /*<<< orphan*/  nouts; struct arc* outs; } ;
struct nfa {int /*<<< orphan*/  cm; int /*<<< orphan*/ * parent; } ;
struct arc {scalar_t__ type; struct arc* freechain; struct arc* outchainRev; struct arc* outchain; struct arc* inchainRev; struct arc* inchain; struct state* to; struct state* from; } ;

/* Variables and functions */
 scalar_t__ COLORED (struct arc*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uncolorchain (int /*<<< orphan*/ ,struct arc*) ; 

__attribute__((used)) static void
freearc(struct nfa *nfa,
		struct arc *victim)
{
	struct state *from = victim->from;
	struct state *to = victim->to;
	struct arc *predecessor;

	assert(victim->type != 0);

	/* take it off color chain if necessary */
	if (COLORED(victim) && nfa->parent == NULL)
		uncolorchain(nfa->cm, victim);

	/* take it off source's out-chain */
	assert(from != NULL);
	predecessor = victim->outchainRev;
	if (predecessor == NULL)
	{
		assert(from->outs == victim);
		from->outs = victim->outchain;
	}
	else
	{
		assert(predecessor->outchain == victim);
		predecessor->outchain = victim->outchain;
	}
	if (victim->outchain != NULL)
	{
		assert(victim->outchain->outchainRev == victim);
		victim->outchain->outchainRev = predecessor;
	}
	from->nouts--;

	/* take it off target's in-chain */
	assert(to != NULL);
	predecessor = victim->inchainRev;
	if (predecessor == NULL)
	{
		assert(to->ins == victim);
		to->ins = victim->inchain;
	}
	else
	{
		assert(predecessor->inchain == victim);
		predecessor->inchain = victim->inchain;
	}
	if (victim->inchain != NULL)
	{
		assert(victim->inchain->inchainRev == victim);
		victim->inchain->inchainRev = predecessor;
	}
	to->nins--;

	/* clean up and place on from-state's free list */
	victim->type = 0;
	victim->from = NULL;		/* precautions... */
	victim->to = NULL;
	victim->inchain = NULL;
	victim->inchainRev = NULL;
	victim->outchain = NULL;
	victim->outchainRev = NULL;
	victim->freechain = from->free;
	from->free = victim;
}