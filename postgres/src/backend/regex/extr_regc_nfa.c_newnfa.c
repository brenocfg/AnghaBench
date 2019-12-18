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
struct vars {int dummy; } ;
struct nfa {void* post; void* final; struct colormap* cm; void* init; void* pre; struct nfa* parent; void** eos; void** bos; struct vars* v; scalar_t__ nstates; int /*<<< orphan*/ * free; int /*<<< orphan*/ * slast; int /*<<< orphan*/ * states; } ;
struct colormap {int dummy; } ;

/* Variables and functions */
 void* COLORLESS ; 
 int /*<<< orphan*/  ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ ISERR () ; 
 scalar_t__ MALLOC (int) ; 
 int /*<<< orphan*/  PLAIN ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  freenfa (struct nfa*) ; 
 int /*<<< orphan*/  newarc (struct nfa*,char,int,void*,void*) ; 
 void* newfstate (struct nfa*,char) ; 
 void* newstate (struct nfa*) ; 
 int /*<<< orphan*/  rainbow (struct nfa*,struct colormap*,int /*<<< orphan*/ ,void*,void*,void*) ; 

__attribute__((used)) static struct nfa *				/* the NFA, or NULL */
newnfa(struct vars *v,
	   struct colormap *cm,
	   struct nfa *parent)		/* NULL if primary NFA */
{
	struct nfa *nfa;

	nfa = (struct nfa *) MALLOC(sizeof(struct nfa));
	if (nfa == NULL)
	{
		ERR(REG_ESPACE);
		return NULL;
	}

	nfa->states = NULL;
	nfa->slast = NULL;
	nfa->free = NULL;
	nfa->nstates = 0;
	nfa->cm = cm;
	nfa->v = v;
	nfa->bos[0] = nfa->bos[1] = COLORLESS;
	nfa->eos[0] = nfa->eos[1] = COLORLESS;
	nfa->parent = parent;		/* Precedes newfstate so parent is valid. */
	nfa->post = newfstate(nfa, '@');	/* number 0 */
	nfa->pre = newfstate(nfa, '>'); /* number 1 */

	nfa->init = newstate(nfa);	/* may become invalid later */
	nfa->final = newstate(nfa);
	if (ISERR())
	{
		freenfa(nfa);
		return NULL;
	}
	rainbow(nfa, nfa->cm, PLAIN, COLORLESS, nfa->pre, nfa->init);
	newarc(nfa, '^', 1, nfa->pre, nfa->init);
	newarc(nfa, '^', 0, nfa->pre, nfa->init);
	rainbow(nfa, nfa->cm, PLAIN, COLORLESS, nfa->final, nfa->post);
	newarc(nfa, '$', 1, nfa->final, nfa->post);
	newarc(nfa, '$', 0, nfa->final, nfa->post);

	if (ISERR())
	{
		freenfa(nfa);
		return NULL;
	}
	return nfa;
}