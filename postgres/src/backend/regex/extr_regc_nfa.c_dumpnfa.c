#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct state {scalar_t__ nouts; struct state* next; } ;
struct nfa {scalar_t__* bos; scalar_t__* eos; int /*<<< orphan*/  cm; int /*<<< orphan*/ * parent; struct state* states; TYPE_2__* post; TYPE_1__* pre; } ;
struct TYPE_4__ {int no; } ;
struct TYPE_3__ {int no; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ COLORLESS ; 
 int /*<<< orphan*/  dumpcolors (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dumpstate (struct state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
dumpnfa(struct nfa *nfa,
		FILE *f)
{
#ifdef REG_DEBUG
	struct state *s;
	int			nstates = 0;
	int			narcs = 0;

	fprintf(f, "pre %d, post %d", nfa->pre->no, nfa->post->no);
	if (nfa->bos[0] != COLORLESS)
		fprintf(f, ", bos [%ld]", (long) nfa->bos[0]);
	if (nfa->bos[1] != COLORLESS)
		fprintf(f, ", bol [%ld]", (long) nfa->bos[1]);
	if (nfa->eos[0] != COLORLESS)
		fprintf(f, ", eos [%ld]", (long) nfa->eos[0]);
	if (nfa->eos[1] != COLORLESS)
		fprintf(f, ", eol [%ld]", (long) nfa->eos[1]);
	fprintf(f, "\n");
	for (s = nfa->states; s != NULL; s = s->next)
	{
		dumpstate(s, f);
		nstates++;
		narcs += s->nouts;
	}
	fprintf(f, "total of %d states, %d arcs\n", nstates, narcs);
	if (nfa->parent == NULL)
		dumpcolors(nfa->cm, f);
	fflush(f);
#endif
}