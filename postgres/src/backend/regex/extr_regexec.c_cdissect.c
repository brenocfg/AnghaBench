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
struct vars {int /*<<< orphan*/  re; } ;
struct subre {int op; int flags; struct subre* left; int /*<<< orphan*/  subno; int /*<<< orphan*/ * right; } ;
typedef  int /*<<< orphan*/  chr ;

/* Variables and functions */
 int BACKR ; 
 scalar_t__ CANCEL_REQUESTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOFF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDEBUG (char*) ; 
 int REG_ASSERT ; 
 int REG_CANCEL ; 
 int REG_ETOOBIG ; 
 int REG_NOMATCH ; 
 int REG_OKAY ; 
 int SHORTER ; 
 scalar_t__ STACK_TOO_DEEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int caltdissect (struct vars*,struct subre*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int cbrdissect (struct vars*,struct subre*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ccondissect (struct vars*,struct subre*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int citerdissect (struct vars*,struct subre*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int crevcondissect (struct vars*,struct subre*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int creviterdissect (struct vars*,struct subre*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  subset (struct vars*,struct subre*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int						/* regexec return code */
cdissect(struct vars *v,
		 struct subre *t,
		 chr *begin,			/* beginning of relevant substring */
		 chr *end)				/* end of same */
{
	int			er;

	assert(t != NULL);
	MDEBUG(("cdissect %ld-%ld %c\n", LOFF(begin), LOFF(end), t->op));

	/* handy place to check for operation cancel */
	if (CANCEL_REQUESTED(v->re))
		return REG_CANCEL;
	/* ... and stack overrun */
	if (STACK_TOO_DEEP(v->re))
		return REG_ETOOBIG;

	switch (t->op)
	{
		case '=':				/* terminal node */
			assert(t->left == NULL && t->right == NULL);
			er = REG_OKAY;		/* no action, parent did the work */
			break;
		case 'b':				/* back reference */
			assert(t->left == NULL && t->right == NULL);
			er = cbrdissect(v, t, begin, end);
			break;
		case '.':				/* concatenation */
			assert(t->left != NULL && t->right != NULL);
			if (t->left->flags & SHORTER)	/* reverse scan */
				er = crevcondissect(v, t, begin, end);
			else
				er = ccondissect(v, t, begin, end);
			break;
		case '|':				/* alternation */
			assert(t->left != NULL);
			er = caltdissect(v, t, begin, end);
			break;
		case '*':				/* iteration */
			assert(t->left != NULL);
			if (t->left->flags & SHORTER)	/* reverse scan */
				er = creviterdissect(v, t, begin, end);
			else
				er = citerdissect(v, t, begin, end);
			break;
		case '(':				/* capturing */
			assert(t->left != NULL && t->right == NULL);
			assert(t->subno > 0);
			er = cdissect(v, t->left, begin, end);
			if (er == REG_OKAY)
				subset(v, t, begin, end);
			break;
		default:
			er = REG_ASSERT;
			break;
	}

	/*
	 * We should never have a match failure unless backrefs lurk below;
	 * otherwise, either caller failed to check the DFA, or there's some
	 * inconsistency between the DFA and the node's innards.
	 */
	assert(er != REG_NOMATCH || (t->flags & BACKR));

	return er;
}