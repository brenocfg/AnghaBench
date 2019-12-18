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
struct neighbour {int nud_state; int /*<<< orphan*/  parms; int /*<<< orphan*/  probes; scalar_t__ updated; scalar_t__ dead; } ;

/* Variables and functions */
 scalar_t__ NEIGH_VAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NUD_FAILED ; 
 int NUD_INCOMPLETE ; 
 int /*<<< orphan*/  RETRANS_TIME ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  neigh_add_timer (struct neighbour*,scalar_t__) ; 
 int /*<<< orphan*/  neigh_max_probes (struct neighbour*) ; 

void __neigh_set_probe_once(struct neighbour *neigh)
{
	if (neigh->dead)
		return;
	neigh->updated = jiffies;
	if (!(neigh->nud_state & NUD_FAILED))
		return;
	neigh->nud_state = NUD_INCOMPLETE;
	atomic_set(&neigh->probes, neigh_max_probes(neigh));
	neigh_add_timer(neigh,
			jiffies + NEIGH_VAR(neigh->parms, RETRANS_TIME));
}