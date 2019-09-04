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
struct sh_eth_private {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int TSU_VTAG0 ; 
 int TSU_VTAG1 ; 

__attribute__((used)) static int sh_eth_get_vtag_index(struct sh_eth_private *mdp)
{
	if (!mdp->port)
		return TSU_VTAG0;
	else
		return TSU_VTAG1;
}