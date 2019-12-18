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
struct ip17xx_state {int dummy; } ;

/* Variables and functions */
 int ip175c_update_state (struct ip17xx_state*) ; 

__attribute__((used)) static int ip175c_set_vlan_mode(struct ip17xx_state *state)
{
	return ip175c_update_state(state);
}