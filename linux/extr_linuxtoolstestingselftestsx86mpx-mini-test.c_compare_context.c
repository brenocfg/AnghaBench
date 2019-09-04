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
typedef  unsigned long uint64_t ;

/* Variables and functions */
 int MPX_BOUNDS_OFFSET ; 
 int /*<<< orphan*/  dprintf3 (char*,int,unsigned long,unsigned long,int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  eprintf (char*,unsigned long,...) ; 
 unsigned long** shadow_plb ; 

__attribute__((used)) static inline bool compare_context(void *__xsave_buffer)
{
	uint64_t *bounds = (uint64_t *)(__xsave_buffer + MPX_BOUNDS_OFFSET);

	int i;
	for (i = 0; i < 4; i++) {
		dprintf3("shadow[%d]{%016lx/%016lx}\nbounds[%d]{%016lx/%016lx}\n",
		       i, (unsigned long)shadow_plb[i][0], (unsigned long)shadow_plb[i][1],
		       i, (unsigned long)bounds[i*2],     ~(unsigned long)bounds[i*2+1]);
		if ((shadow_plb[i][0] != bounds[i*2]) ||
		    (shadow_plb[i][1] != ~(unsigned long)bounds[i*2+1])) {
			eprintf("ERROR comparing shadow to real bound register %d\n", i);
			eprintf("shadow{0x%016lx/0x%016lx}\nbounds{0x%016lx/0x%016lx}\n",
			       (unsigned long)shadow_plb[i][0], (unsigned long)shadow_plb[i][1],
			       (unsigned long)bounds[i*2], (unsigned long)bounds[i*2+1]);
			return false;
		}
	}

	return true;
}