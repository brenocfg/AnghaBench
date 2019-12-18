#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vars {int dummy; } ;
struct subre {char op; TYPE_2__* right; TYPE_2__* left; int /*<<< orphan*/  id; } ;
struct dfa {int dummy; } ;
typedef  int /*<<< orphan*/  chr ;
struct TYPE_5__ {scalar_t__ nstates; } ;
struct TYPE_6__ {int flags; TYPE_1__ cnfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOFF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MDEBUG (char*) ; 
 int /*<<< orphan*/  NOERR () ; 
 int REG_ASSERT ; 
 int REG_NOMATCH ; 
 int REG_OKAY ; 
 int SHORTER ; 
 int /*<<< orphan*/  assert (int) ; 
 int cdissect (struct vars*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dfa* getsubdfa (struct vars*,TYPE_2__*) ; 
 int /*<<< orphan*/ * longest (struct vars*,struct dfa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * shortest (struct vars*,struct dfa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  zaptreesubs (struct vars*,TYPE_2__*) ; 

__attribute__((used)) static int						/* regexec return code */
crevcondissect(struct vars *v,
			   struct subre *t,
			   chr *begin,		/* beginning of relevant substring */
			   chr *end)		/* end of same */
{
	struct dfa *d;
	struct dfa *d2;
	chr		   *mid;
	int			er;

	assert(t->op == '.');
	assert(t->left != NULL && t->left->cnfa.nstates > 0);
	assert(t->right != NULL && t->right->cnfa.nstates > 0);
	assert(t->left->flags & SHORTER);

	d = getsubdfa(v, t->left);
	NOERR();
	d2 = getsubdfa(v, t->right);
	NOERR();
	MDEBUG(("crevcon %d\n", t->id));

	/* pick a tentative midpoint */
	mid = shortest(v, d, begin, begin, end, (chr **) NULL, (int *) NULL);
	NOERR();
	if (mid == NULL)
		return REG_NOMATCH;
	MDEBUG(("tentative midpoint %ld\n", LOFF(mid)));

	/* iterate until satisfaction or failure */
	for (;;)
	{
		/* try this midpoint on for size */
		if (longest(v, d2, mid, end, (int *) NULL) == end)
		{
			er = cdissect(v, t->left, begin, mid);
			if (er == REG_OKAY)
			{
				er = cdissect(v, t->right, mid, end);
				if (er == REG_OKAY)
				{
					/* satisfaction */
					MDEBUG(("successful\n"));
					return REG_OKAY;
				}
			}
			if (er != REG_NOMATCH)
				return er;
		}
		NOERR();

		/* that midpoint didn't work, find a new one */
		if (mid == end)
		{
			/* all possibilities exhausted */
			MDEBUG(("%d no midpoint\n", t->id));
			return REG_NOMATCH;
		}
		mid = shortest(v, d, begin, mid + 1, end, (chr **) NULL, (int *) NULL);
		NOERR();
		if (mid == NULL)
		{
			/* failed to find a new one */
			MDEBUG(("%d failed midpoint\n", t->id));
			return REG_NOMATCH;
		}
		MDEBUG(("%d: new midpoint %ld\n", t->id, LOFF(mid)));
		zaptreesubs(v, t->left);
		zaptreesubs(v, t->right);
	}

	/* can't get here */
	return REG_ASSERT;
}