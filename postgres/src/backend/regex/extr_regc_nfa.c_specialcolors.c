#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfa {scalar_t__* bos; scalar_t__* eos; TYPE_1__* parent; int /*<<< orphan*/  cm; } ;
struct TYPE_2__ {scalar_t__* bos; scalar_t__* eos; } ;

/* Variables and functions */
 scalar_t__ COLORLESS ; 
 int /*<<< orphan*/  assert (int) ; 
 void* pseudocolor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
specialcolors(struct nfa *nfa)
{
	/* false colors for BOS, BOL, EOS, EOL */
	if (nfa->parent == NULL)
	{
		nfa->bos[0] = pseudocolor(nfa->cm);
		nfa->bos[1] = pseudocolor(nfa->cm);
		nfa->eos[0] = pseudocolor(nfa->cm);
		nfa->eos[1] = pseudocolor(nfa->cm);
	}
	else
	{
		assert(nfa->parent->bos[0] != COLORLESS);
		nfa->bos[0] = nfa->parent->bos[0];
		assert(nfa->parent->bos[1] != COLORLESS);
		nfa->bos[1] = nfa->parent->bos[1];
		assert(nfa->parent->eos[0] != COLORLESS);
		nfa->eos[0] = nfa->parent->eos[0];
		assert(nfa->parent->eos[1] != COLORLESS);
		nfa->eos[1] = nfa->parent->eos[1];
	}
}