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
struct TYPE_4__ {struct arcbatch* next; struct arc* a; } ;
struct state {int noas; struct arc* free; TYPE_2__ oas; } ;
struct nfa {TYPE_1__* v; } ;
struct arcbatch {struct arc* a; struct arcbatch* next; } ;
struct arc {struct arc* freechain; scalar_t__ type; } ;
struct TYPE_3__ {scalar_t__ spaceused; } ;

/* Variables and functions */
 int ABSIZE ; 
 scalar_t__ MALLOC (int) ; 
 int /*<<< orphan*/  NERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_ESPACE ; 
 int /*<<< orphan*/  REG_ETOOBIG ; 
 scalar_t__ REG_MAX_COMPILE_SPACE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct arc *				/* NULL for failure */
allocarc(struct nfa *nfa,
		 struct state *s)
{
	struct arc *a;

	/* shortcut */
	if (s->free == NULL && s->noas < ABSIZE)
	{
		a = &s->oas.a[s->noas];
		s->noas++;
		return a;
	}

	/* if none at hand, get more */
	if (s->free == NULL)
	{
		struct arcbatch *newAb;
		int			i;

		if (nfa->v->spaceused >= REG_MAX_COMPILE_SPACE)
		{
			NERR(REG_ETOOBIG);
			return NULL;
		}
		newAb = (struct arcbatch *) MALLOC(sizeof(struct arcbatch));
		if (newAb == NULL)
		{
			NERR(REG_ESPACE);
			return NULL;
		}
		nfa->v->spaceused += sizeof(struct arcbatch);
		newAb->next = s->oas.next;
		s->oas.next = newAb;

		for (i = 0; i < ABSIZE; i++)
		{
			newAb->a[i].type = 0;
			newAb->a[i].freechain = &newAb->a[i + 1];
		}
		newAb->a[ABSIZE - 1].freechain = NULL;
		s->free = &newAb->a[0];
	}
	assert(s->free != NULL);

	a = s->free;
	s->free = a->freechain;
	return a;
}