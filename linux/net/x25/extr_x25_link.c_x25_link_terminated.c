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
struct x25_neigh {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  X25_LINK_STATE_0 ; 
 int /*<<< orphan*/  x25_kill_by_neigh (struct x25_neigh*) ; 

void x25_link_terminated(struct x25_neigh *nb)
{
	nb->state = X25_LINK_STATE_0;
	/* Out of order: clear existing virtual calls (X.25 03/93 4.6.3) */
	x25_kill_by_neigh(nb);
}