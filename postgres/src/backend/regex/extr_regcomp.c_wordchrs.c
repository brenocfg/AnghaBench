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
struct vars {struct state* wordchrs; int /*<<< orphan*/ * savenow; int /*<<< orphan*/  nfa; } ;
struct state {int dummy; } ;

/* Variables and functions */
 scalar_t__ ISERR () ; 
 int /*<<< orphan*/  NEXT () ; 
 int /*<<< orphan*/  NOERR () ; 
 scalar_t__ SEE (char) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bracket (struct vars*,struct state*,struct state*) ; 
 int /*<<< orphan*/  lexword (struct vars*) ; 
 struct state* newstate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wordchrs(struct vars *v)
{
	struct state *left;
	struct state *right;

	if (v->wordchrs != NULL)
	{
		NEXT();					/* for consistency */
		return;
	}

	left = newstate(v->nfa);
	right = newstate(v->nfa);
	NOERR();
	/* fine point:	implemented with [::], and lexer will set REG_ULOCALE */
	lexword(v);
	NEXT();
	assert(v->savenow != NULL && SEE('['));
	bracket(v, left, right);
	assert((v->savenow != NULL && SEE(']')) || ISERR());
	NEXT();
	NOERR();
	v->wordchrs = left;
}