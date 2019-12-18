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
struct vars {int /*<<< orphan*/  nfa; int /*<<< orphan*/  cm; } ;
struct subre {int /*<<< orphan*/  cnfa; int /*<<< orphan*/  end; int /*<<< orphan*/ * begin; } ;
struct nfa {int /*<<< orphan*/  final; int /*<<< orphan*/  init; } ;
typedef  int /*<<< orphan*/  idbuf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ISERR () ; 
 int /*<<< orphan*/  NOERRZ () ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compact (struct nfa*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dupnfa (struct nfa*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  freenfa (struct nfa*) ; 
 int /*<<< orphan*/  makesearch (struct vars*,struct nfa*) ; 
 struct nfa* newnfa (struct vars*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long optimize (struct nfa*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  specialcolors (struct nfa*) ; 
 char* stid (struct subre*,char*,int) ; 

__attribute__((used)) static long						/* optimize results */
nfanode(struct vars *v,
		struct subre *t,
		int converttosearch,
		FILE *f)				/* for debug output */
{
	struct nfa *nfa;
	long		ret = 0;

	assert(t->begin != NULL);

#ifdef REG_DEBUG
	if (f != NULL)
	{
		char		idbuf[50];

		fprintf(f, "\n\n\n========= TREE NODE %s ==========\n",
				stid(t, idbuf, sizeof(idbuf)));
	}
#endif
	nfa = newnfa(v, v->cm, v->nfa);
	NOERRZ();
	dupnfa(nfa, t->begin, t->end, nfa->init, nfa->final);
	if (!ISERR())
		specialcolors(nfa);
	if (!ISERR())
		ret = optimize(nfa, f);
	if (converttosearch && !ISERR())
		makesearch(v, nfa);
	if (!ISERR())
		compact(nfa, &t->cnfa);

	freenfa(nfa);
	return ret;
}