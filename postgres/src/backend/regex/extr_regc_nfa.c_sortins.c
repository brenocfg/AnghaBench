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
struct state {int nins; struct arc* ins; } ;
struct nfa {int dummy; } ;
struct arc {struct arc* inchainRev; struct arc* inchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct arc**) ; 
 scalar_t__ MALLOC (int) ; 
 int /*<<< orphan*/  NERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  qsort (struct arc**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sortins_cmp ; 

__attribute__((used)) static void
sortins(struct nfa *nfa,
		struct state *s)
{
	struct arc **sortarray;
	struct arc *a;
	int			n = s->nins;
	int			i;

	if (n <= 1)
		return;					/* nothing to do */
	/* make an array of arc pointers ... */
	sortarray = (struct arc **) MALLOC(n * sizeof(struct arc *));
	if (sortarray == NULL)
	{
		NERR(REG_ESPACE);
		return;
	}
	i = 0;
	for (a = s->ins; a != NULL; a = a->inchain)
		sortarray[i++] = a;
	assert(i == n);
	/* ... sort the array */
	qsort(sortarray, n, sizeof(struct arc *), sortins_cmp);
	/* ... and rebuild arc list in order */
	/* it seems worth special-casing first and last items to simplify loop */
	a = sortarray[0];
	s->ins = a;
	a->inchain = sortarray[1];
	a->inchainRev = NULL;
	for (i = 1; i < n - 1; i++)
	{
		a = sortarray[i];
		a->inchain = sortarray[i + 1];
		a->inchainRev = sortarray[i - 1];
	}
	a = sortarray[i];
	a->inchain = NULL;
	a->inchainRev = sortarray[i - 1];
	FREE(sortarray);
}