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

/* Variables and functions */
 int /*<<< orphan*/  AUI ; 
 int /*<<< orphan*/  BNC ; 
 int /*<<< orphan*/  Backplane ; 
 int /*<<< orphan*/  FIBRE ; 
 int /*<<< orphan*/  MII ; 
 int /*<<< orphan*/  TP ; 
 int /*<<< orphan*/  phylink_set (unsigned long*,int /*<<< orphan*/ ) ; 

void phylink_set_port_modes(unsigned long *mask)
{
	phylink_set(mask, TP);
	phylink_set(mask, AUI);
	phylink_set(mask, MII);
	phylink_set(mask, FIBRE);
	phylink_set(mask, BNC);
	phylink_set(mask, Backplane);
}