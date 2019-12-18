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
struct subre {int flags; char op; struct subre* right; struct subre* left; } ;
struct state {int dummy; } ;

/* Variables and functions */
 scalar_t__ EAT (char) ; 
 int /*<<< orphan*/  EMPTYARC (struct state*,struct state*) ; 
 int EOS ; 
 int /*<<< orphan*/  ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LONGER ; 
 int /*<<< orphan*/  MESSY (int) ; 
 int /*<<< orphan*/  NOERRN () ; 
 int /*<<< orphan*/  REG_EPAREN ; 
 scalar_t__ SEE (int) ; 
 int UP (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  freesubre (struct vars*,struct subre*) ; 
 struct state* newstate (int /*<<< orphan*/ ) ; 
 struct subre* parsebranch (struct vars*,int,int,struct state*,struct state*,int /*<<< orphan*/ ) ; 
 void* subre (struct vars*,char,int /*<<< orphan*/ ,struct state*,struct state*) ; 

__attribute__((used)) static struct subre *
parse(struct vars *v,
	  int stopper,				/* EOS or ')' */
	  int type,					/* LACON (lookaround subRE) or PLAIN */
	  struct state *init,		/* initial state */
	  struct state *final)		/* final state */
{
	struct state *left;			/* scaffolding for branch */
	struct state *right;
	struct subre *branches;		/* top level */
	struct subre *branch;		/* current branch */
	struct subre *t;			/* temporary */
	int			firstbranch;	/* is this the first branch? */

	assert(stopper == ')' || stopper == EOS);

	branches = subre(v, '|', LONGER, init, final);
	NOERRN();
	branch = branches;
	firstbranch = 1;
	do
	{							/* a branch */
		if (!firstbranch)
		{
			/* need a place to hang it */
			branch->right = subre(v, '|', LONGER, init, final);
			NOERRN();
			branch = branch->right;
		}
		firstbranch = 0;
		left = newstate(v->nfa);
		right = newstate(v->nfa);
		NOERRN();
		EMPTYARC(init, left);
		EMPTYARC(right, final);
		NOERRN();
		branch->left = parsebranch(v, stopper, type, left, right, 0);
		NOERRN();
		branch->flags |= UP(branch->flags | branch->left->flags);
		if ((branch->flags & ~branches->flags) != 0)	/* new flags */
			for (t = branches; t != branch; t = t->right)
				t->flags |= branch->flags;
	} while (EAT('|'));
	assert(SEE(stopper) || SEE(EOS));

	if (!SEE(stopper))
	{
		assert(stopper == ')' && SEE(EOS));
		ERR(REG_EPAREN);
	}

	/* optimize out simple cases */
	if (branch == branches)
	{							/* only one branch */
		assert(branch->right == NULL);
		t = branch->left;
		branch->left = NULL;
		freesubre(v, branches);
		branches = t;
	}
	else if (!MESSY(branches->flags))
	{							/* no interesting innards */
		freesubre(v, branches->left);
		branches->left = NULL;
		freesubre(v, branches->right);
		branches->right = NULL;
		branches->op = '=';
	}

	return branches;
}