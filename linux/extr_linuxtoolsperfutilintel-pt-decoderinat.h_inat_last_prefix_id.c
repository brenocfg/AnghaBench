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
typedef  int insn_attr_t ;

/* Variables and functions */
 int INAT_LSTPFX_MAX ; 
 int INAT_PFX_MASK ; 

__attribute__((used)) static inline int inat_last_prefix_id(insn_attr_t attr)
{
	if ((attr & INAT_PFX_MASK) > INAT_LSTPFX_MAX)
		return 0;
	else
		return attr & INAT_PFX_MASK;
}