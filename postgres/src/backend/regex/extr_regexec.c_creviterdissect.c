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
struct vars {int err; } ;
struct subre {char op; int min; size_t max; int /*<<< orphan*/  id; TYPE_2__* left; } ;
struct dfa {int dummy; } ;
typedef  int /*<<< orphan*/  chr ;
struct TYPE_5__ {scalar_t__ nstates; } ;
struct TYPE_6__ {int flags; TYPE_1__ cnfa; } ;

/* Variables and functions */
 size_t DUPINF ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ **) ; 
 scalar_t__ ISERR () ; 
 int /*<<< orphan*/  LOFF (int /*<<< orphan*/ *) ; 
 scalar_t__ MALLOC (size_t) ; 
 int /*<<< orphan*/  MDEBUG (char*) ; 
 int REG_ESPACE ; 
 int REG_NOMATCH ; 
 int REG_OKAY ; 
 int SHORTER ; 
 int /*<<< orphan*/  assert (int) ; 
 int cdissect (struct vars*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct dfa* getsubdfa (struct vars*,TYPE_2__*) ; 
 int /*<<< orphan*/ * shortest (struct vars*,struct dfa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  zaptreesubs (struct vars*,TYPE_2__*) ; 

__attribute__((used)) static int						/* regexec return code */
creviterdissect(struct vars *v,
				struct subre *t,
				chr *begin,		/* beginning of relevant substring */
				chr *end)		/* end of same */
{
	struct dfa *d;
	chr		  **endpts;
	chr		   *limit;
	int			min_matches;
	size_t		max_matches;
	int			nverified;
	int			k;
	int			i;
	int			er;

	assert(t->op == '*');
	assert(t->left != NULL && t->left->cnfa.nstates > 0);
	assert(t->left->flags & SHORTER);
	assert(begin <= end);

	/*
	 * If zero matches are allowed, and target string is empty, just declare
	 * victory.  OTOH, if target string isn't empty, zero matches can't work
	 * so we pretend the min is 1.
	 */
	min_matches = t->min;
	if (min_matches <= 0)
	{
		if (begin == end)
			return REG_OKAY;
		min_matches = 1;
	}

	/*
	 * We need workspace to track the endpoints of each sub-match.  Normally
	 * we consider only nonzero-length sub-matches, so there can be at most
	 * end-begin of them.  However, if min is larger than that, we will also
	 * consider zero-length sub-matches in order to find enough matches.
	 *
	 * For convenience, endpts[0] contains the "begin" pointer and we store
	 * sub-match endpoints in endpts[1..max_matches].
	 */
	max_matches = end - begin;
	if (max_matches > t->max && t->max != DUPINF)
		max_matches = t->max;
	if (max_matches < min_matches)
		max_matches = min_matches;
	endpts = (chr **) MALLOC((max_matches + 1) * sizeof(chr *));
	if (endpts == NULL)
		return REG_ESPACE;
	endpts[0] = begin;

	d = getsubdfa(v, t->left);
	if (ISERR())
	{
		FREE(endpts);
		return v->err;
	}
	MDEBUG(("creviter %d\n", t->id));

	/*
	 * Our strategy is to first find a set of sub-match endpoints that are
	 * valid according to the child node's DFA, and then recursively dissect
	 * each sub-match to confirm validity.  If any validity check fails,
	 * backtrack the last sub-match and try again.  And, when we next try for
	 * a validity check, we need not recheck any successfully verified
	 * sub-matches that we didn't move the endpoints of.  nverified remembers
	 * how many sub-matches are currently known okay.
	 */

	/* initialize to consider first sub-match */
	nverified = 0;
	k = 1;
	limit = begin;

	/* iterate until satisfaction or failure */
	while (k > 0)
	{
		/* disallow zero-length match unless necessary to achieve min */
		if (limit == endpts[k - 1] &&
			limit != end &&
			(k >= min_matches || min_matches - k < end - limit))
			limit++;

		/* if this is the last allowed sub-match, it must reach to the end */
		if (k >= max_matches)
			limit = end;

		/* try to find an endpoint for the k'th sub-match */
		endpts[k] = shortest(v, d, endpts[k - 1], limit, end,
							 (chr **) NULL, (int *) NULL);
		if (ISERR())
		{
			FREE(endpts);
			return v->err;
		}
		if (endpts[k] == NULL)
		{
			/* no match possible, so see if we can lengthen previous one */
			k--;
			goto backtrack;
		}
		MDEBUG(("%d: working endpoint %d: %ld\n",
				t->id, k, LOFF(endpts[k])));

		/* k'th sub-match can no longer be considered verified */
		if (nverified >= k)
			nverified = k - 1;

		if (endpts[k] != end)
		{
			/* haven't reached end yet, try another iteration if allowed */
			if (k >= max_matches)
			{
				/* must try to lengthen some previous match */
				k--;
				goto backtrack;
			}

			k++;
			limit = endpts[k - 1];
			continue;
		}

		/*
		 * We've identified a way to divide the string into k sub-matches that
		 * works so far as the child DFA can tell.  If k is an allowed number
		 * of matches, start the slow part: recurse to verify each sub-match.
		 * We always have k <= max_matches, needn't check that.
		 */
		if (k < min_matches)
			goto backtrack;

		MDEBUG(("%d: verifying %d..%d\n", t->id, nverified + 1, k));

		for (i = nverified + 1; i <= k; i++)
		{
			zaptreesubs(v, t->left);
			er = cdissect(v, t->left, endpts[i - 1], endpts[i]);
			if (er == REG_OKAY)
			{
				nverified = i;
				continue;
			}
			if (er == REG_NOMATCH)
				break;
			/* oops, something failed */
			FREE(endpts);
			return er;
		}

		if (i > k)
		{
			/* satisfaction */
			MDEBUG(("%d successful\n", t->id));
			FREE(endpts);
			return REG_OKAY;
		}

		/* match failed to verify, so backtrack */

backtrack:

		/*
		 * Must consider longer versions of the current sub-match.
		 */
		while (k > 0)
		{
			if (endpts[k] < end)
			{
				limit = endpts[k] + 1;
				/* break out of backtrack loop, continue the outer one */
				break;
			}
			/* can't lengthen k'th sub-match any more, consider previous one */
			k--;
		}
	}

	/* all possibilities exhausted */
	MDEBUG(("%d failed\n", t->id));
	FREE(endpts);
	return REG_NOMATCH;
}