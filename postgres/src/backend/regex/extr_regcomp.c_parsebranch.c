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
struct vars {int /*<<< orphan*/  nfa; } ;
struct subre {int dummy; } ;
struct state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTYARC (struct state*,struct state*) ; 
 int EOS ; 
 int /*<<< orphan*/  NOERRN () ; 
 int /*<<< orphan*/  NOTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UUNSPEC ; 
 int /*<<< orphan*/  SEE (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  moveins (int /*<<< orphan*/ ,struct state*,struct state*) ; 
 struct state* newstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parseqatom (struct vars*,int,int,struct state*,struct state*,struct subre*) ; 
 struct subre* subre (struct vars*,char,int /*<<< orphan*/ ,struct state*,struct state*) ; 

__attribute__((used)) static struct subre *
parsebranch(struct vars *v,
			int stopper,		/* EOS or ')' */
			int type,			/* LACON (lookaround subRE) or PLAIN */
			struct state *left, /* leftmost state */
			struct state *right,	/* rightmost state */
			int partial)		/* is this only part of a branch? */
{
	struct state *lp;			/* left end of current construct */
	int			seencontent;	/* is there anything in this branch yet? */
	struct subre *t;

	lp = left;
	seencontent = 0;
	t = subre(v, '=', 0, left, right);	/* op '=' is tentative */
	NOERRN();
	while (!SEE('|') && !SEE(stopper) && !SEE(EOS))
	{
		if (seencontent)
		{						/* implicit concat operator */
			lp = newstate(v->nfa);
			NOERRN();
			moveins(v->nfa, right, lp);
		}
		seencontent = 1;

		/* NB, recursion in parseqatom() may swallow rest of branch */
		parseqatom(v, stopper, type, lp, right, t);
		NOERRN();
	}

	if (!seencontent)
	{							/* empty branch */
		if (!partial)
			NOTE(REG_UUNSPEC);
		assert(lp == left);
		EMPTYARC(left, right);
	}

	return t;
}