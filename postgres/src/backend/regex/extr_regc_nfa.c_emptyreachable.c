#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct state {size_t no; struct state* tmp; } ;
struct nfa {TYPE_1__* v; } ;
struct arc {scalar_t__ type; struct state* from; struct arc* inchain; } ;
struct TYPE_2__ {int /*<<< orphan*/  re; } ;

/* Variables and functions */
 scalar_t__ EMPTY ; 
 int /*<<< orphan*/  NERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_ETOOBIG ; 
 scalar_t__ STACK_TOO_DEEP (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct state *
emptyreachable(struct nfa *nfa,
			   struct state *s,
			   struct state *lastfound,
			   struct arc **inarcsorig)
{
	struct arc *a;

	/* Since this is recursive, it could be driven to stack overflow */
	if (STACK_TOO_DEEP(nfa->v->re))
	{
		NERR(REG_ETOOBIG);
		return lastfound;
	}

	s->tmp = lastfound;
	lastfound = s;
	for (a = inarcsorig[s->no]; a != NULL; a = a->inchain)
	{
		if (a->type == EMPTY && a->from->tmp == NULL)
			lastfound = emptyreachable(nfa, a->from, lastfound, inarcsorig);
	}
	return lastfound;
}