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
struct state {int dummy; } ;
struct nfa {int dummy; } ;
struct arc {int /*<<< orphan*/  co; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  newarc (struct nfa*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct state*,struct state*) ; 

__attribute__((used)) static void
cparc(struct nfa *nfa,
	  struct arc *oa,
	  struct state *from,
	  struct state *to)
{
	newarc(nfa, oa->type, oa->co, from, to);
}