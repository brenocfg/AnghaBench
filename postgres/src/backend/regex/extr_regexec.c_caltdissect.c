#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vars {int dummy; } ;
struct subre {char op; struct subre* right; TYPE_2__* left; int /*<<< orphan*/  id; } ;
struct dfa {int dummy; } ;
typedef  int /*<<< orphan*/  chr ;
struct TYPE_4__ {scalar_t__ nstates; } ;
struct TYPE_5__ {TYPE_1__ cnfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDEBUG (char*) ; 
 int /*<<< orphan*/  NOERR () ; 
 int REG_NOMATCH ; 
 int /*<<< orphan*/  assert (int) ; 
 int cdissect (struct vars*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dfa* getsubdfa (struct vars*,TYPE_2__*) ; 
 int /*<<< orphan*/ * longest (struct vars*,struct dfa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int						/* regexec return code */
caltdissect(struct vars *v,
			struct subre *t,
			chr *begin,			/* beginning of relevant substring */
			chr *end)			/* end of same */
{
	struct dfa *d;
	int			er;

	/* We loop, rather than tail-recurse, to handle a chain of alternatives */
	while (t != NULL)
	{
		assert(t->op == '|');
		assert(t->left != NULL && t->left->cnfa.nstates > 0);

		MDEBUG(("calt n%d\n", t->id));

		d = getsubdfa(v, t->left);
		NOERR();
		if (longest(v, d, begin, end, (int *) NULL) == end)
		{
			MDEBUG(("calt matched\n"));
			er = cdissect(v, t->left, begin, end);
			if (er != REG_NOMATCH)
				return er;
		}
		NOERR();

		t = t->right;
	}

	return REG_NOMATCH;
}