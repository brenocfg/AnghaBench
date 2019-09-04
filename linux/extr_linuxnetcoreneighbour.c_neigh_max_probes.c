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
struct neighbour {int nud_state; struct neigh_parms* parms; } ;
struct neigh_parms {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_PROBES ; 
 int /*<<< orphan*/  MCAST_PROBES ; 
 int /*<<< orphan*/  MCAST_REPROBES ; 
 int NEIGH_VAR (struct neigh_parms*,int /*<<< orphan*/ ) ; 
 int NUD_PROBE ; 
 int /*<<< orphan*/  UCAST_PROBES ; 

__attribute__((used)) static __inline__ int neigh_max_probes(struct neighbour *n)
{
	struct neigh_parms *p = n->parms;
	return NEIGH_VAR(p, UCAST_PROBES) + NEIGH_VAR(p, APP_PROBES) +
	       (n->nud_state & NUD_PROBE ? NEIGH_VAR(p, MCAST_REPROBES) :
	        NEIGH_VAR(p, MCAST_PROBES));
}