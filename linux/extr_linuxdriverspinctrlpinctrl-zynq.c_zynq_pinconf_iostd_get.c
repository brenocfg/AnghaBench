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
typedef  unsigned int u32 ;

/* Variables and functions */
 unsigned int ZYNQ_PINCONF_IOTYPE_MASK ; 
 unsigned int ZYNQ_PINCONF_IOTYPE_SHIFT ; 

__attribute__((used)) static unsigned int zynq_pinconf_iostd_get(u32 reg)
{
	return (reg & ZYNQ_PINCONF_IOTYPE_MASK) >> ZYNQ_PINCONF_IOTYPE_SHIFT;
}