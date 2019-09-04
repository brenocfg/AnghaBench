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
struct neighbour {int nud_state; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int NUD_IN_TIMER ; 
 scalar_t__ del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 

__attribute__((used)) static int neigh_del_timer(struct neighbour *n)
{
	if ((n->nud_state & NUD_IN_TIMER) &&
	    del_timer(&n->timer)) {
		neigh_release(n);
		return 1;
	}
	return 0;
}