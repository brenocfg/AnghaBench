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
struct state {int /*<<< orphan*/  nins; struct arc* ins; } ;
struct arc {struct arc* inchainRev; struct arc* inchain; struct state* to; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
changearctarget(struct arc *a, struct state *newto)
{
	struct state *oldto = a->to;
	struct arc *predecessor;

	assert(oldto != newto);

	/* take it off old target's in-chain */
	assert(oldto != NULL);
	predecessor = a->inchainRev;
	if (predecessor == NULL)
	{
		assert(oldto->ins == a);
		oldto->ins = a->inchain;
	}
	else
	{
		assert(predecessor->inchain == a);
		predecessor->inchain = a->inchain;
	}
	if (a->inchain != NULL)
	{
		assert(a->inchain->inchainRev == a);
		a->inchain->inchainRev = predecessor;
	}
	oldto->nins--;

	a->to = newto;

	/* prepend it to new target's in-chain */
	a->inchain = newto->ins;
	a->inchainRev = NULL;
	if (newto->ins)
		newto->ins->inchainRev = a;
	newto->ins = a;
	newto->nins++;
}