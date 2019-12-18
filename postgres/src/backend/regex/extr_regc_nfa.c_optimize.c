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
struct nfa {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 long analyze (struct nfa*) ; 
 int /*<<< orphan*/  cleanup (struct nfa*) ; 
 int /*<<< orphan*/  dumpnfa (struct nfa*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fixconstraintloops (struct nfa*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fixempties (struct nfa*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pullback (struct nfa*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pushfwd (struct nfa*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static long						/* re_info bits */
optimize(struct nfa *nfa,
		 FILE *f)				/* for debug output; NULL none */
{
#ifdef REG_DEBUG
	int			verbose = (f != NULL) ? 1 : 0;

	if (verbose)
		fprintf(f, "\ninitial cleanup:\n");
#endif
	cleanup(nfa);				/* may simplify situation */
#ifdef REG_DEBUG
	if (verbose)
		dumpnfa(nfa, f);
	if (verbose)
		fprintf(f, "\nempties:\n");
#endif
	fixempties(nfa, f);			/* get rid of EMPTY arcs */
#ifdef REG_DEBUG
	if (verbose)
		fprintf(f, "\nconstraints:\n");
#endif
	fixconstraintloops(nfa, f); /* get rid of constraint loops */
	pullback(nfa, f);			/* pull back constraints backward */
	pushfwd(nfa, f);			/* push fwd constraints forward */
#ifdef REG_DEBUG
	if (verbose)
		fprintf(f, "\nfinal cleanup:\n");
#endif
	cleanup(nfa);				/* final tidying */
#ifdef REG_DEBUG
	if (verbose)
		dumpnfa(nfa, f);
#endif
	return analyze(nfa);		/* and analysis */
}