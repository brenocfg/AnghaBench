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
 unsigned char clk_gat_sce (unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned char gat_sce(unsigned int which, unsigned int chan,
			     unsigned int source)
{
	return clk_gat_sce(which, chan, source);
}