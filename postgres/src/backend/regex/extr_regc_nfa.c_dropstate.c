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
struct state {struct arc* outs; struct arc* ins; } ;
struct nfa {int dummy; } ;
struct arc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  freearc (struct nfa*,struct arc*) ; 
 int /*<<< orphan*/  freestate (struct nfa*,struct state*) ; 

__attribute__((used)) static void
dropstate(struct nfa *nfa,
		  struct state *s)
{
	struct arc *a;

	while ((a = s->ins) != NULL)
		freearc(nfa, a);
	while ((a = s->outs) != NULL)
		freearc(nfa, a);
	freestate(nfa, s);
}