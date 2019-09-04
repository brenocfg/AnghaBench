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
struct neighbour {int nud_state; } ;

/* Variables and functions */
 unsigned int ATF_COM ; 
 unsigned int ATF_PERM ; 
 int NUD_PERMANENT ; 
 int NUD_VALID ; 

__attribute__((used)) static unsigned int arp_state_to_flags(struct neighbour *neigh)
{
	if (neigh->nud_state&NUD_PERMANENT)
		return ATF_PERM | ATF_COM;
	else if (neigh->nud_state&NUD_VALID)
		return ATF_COM;
	else
		return 0;
}