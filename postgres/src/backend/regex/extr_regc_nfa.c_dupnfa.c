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
struct state {struct state* tmp; } ;
struct nfa {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY ; 
 int /*<<< orphan*/  cleartraverse (struct nfa*,struct state*) ; 
 int /*<<< orphan*/  duptraverse (struct nfa*,struct state*,struct state*) ; 
 int /*<<< orphan*/  newarc (struct nfa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct state*,struct state*) ; 

__attribute__((used)) static void
dupnfa(struct nfa *nfa,
	   struct state *start,		/* duplicate of subNFA starting here */
	   struct state *stop,		/* and stopping here */
	   struct state *from,		/* stringing duplicate from here */
	   struct state *to)		/* to here */
{
	if (start == stop)
	{
		newarc(nfa, EMPTY, 0, from, to);
		return;
	}

	stop->tmp = to;
	duptraverse(nfa, start, from);
	/* done, except for clearing out the tmp pointers */

	stop->tmp = NULL;
	cleartraverse(nfa, start);
}