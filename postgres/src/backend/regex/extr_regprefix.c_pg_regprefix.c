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
struct guts {int info; int /*<<< orphan*/  cmap; TYPE_1__* tree; } ;
struct cnfa {int nstates; } ;
struct TYPE_5__ {scalar_t__ re_magic; int re_csize; scalar_t__ re_guts; int /*<<< orphan*/  re_collation; } ;
typedef  TYPE_2__ regex_t ;
typedef  int /*<<< orphan*/  chr ;
struct TYPE_4__ {struct cnfa cnfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *) ; 
 scalar_t__ MALLOC (int) ; 
 int REG_ESPACE ; 
 int REG_EXACT ; 
 int REG_INVARG ; 
 int REG_MIXED ; 
 int REG_NOMATCH ; 
 int REG_PREFIX ; 
 int REG_UIMPOSSIBLE ; 
 scalar_t__ REMAGIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int findprefix (struct cnfa*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  pg_set_regex_collation (int /*<<< orphan*/ ) ; 

int
pg_regprefix(regex_t *re,
			 chr **string,
			 size_t *slength)
{
	struct guts *g;
	struct cnfa *cnfa;
	int			st;

	/* sanity checks */
	if (string == NULL || slength == NULL)
		return REG_INVARG;
	*string = NULL;				/* initialize for failure cases */
	*slength = 0;
	if (re == NULL || re->re_magic != REMAGIC)
		return REG_INVARG;
	if (re->re_csize != sizeof(chr))
		return REG_MIXED;

	/* Initialize locale-dependent support */
	pg_set_regex_collation(re->re_collation);

	/* setup */
	g = (struct guts *) re->re_guts;
	if (g->info & REG_UIMPOSSIBLE)
		return REG_NOMATCH;

	/*
	 * This implementation considers only the search NFA for the topmost regex
	 * tree node.  Therefore, constraints such as backrefs are not fully
	 * applied, which is allowed per the function's API spec.
	 */
	assert(g->tree != NULL);
	cnfa = &g->tree->cnfa;

	/*
	 * Since a correct NFA should never contain any exit-free loops, it should
	 * not be possible for our traversal to return to a previously visited NFA
	 * state.  Hence we need at most nstates chrs in the output string.
	 */
	*string = (chr *) MALLOC(cnfa->nstates * sizeof(chr));
	if (*string == NULL)
		return REG_ESPACE;

	/* do it */
	st = findprefix(cnfa, &g->cmap, *string, slength);

	assert(*slength <= cnfa->nstates);

	/* clean up */
	if (st != REG_PREFIX && st != REG_EXACT)
	{
		FREE(*string);
		*string = NULL;
		*slength = 0;
	}

	return st;
}