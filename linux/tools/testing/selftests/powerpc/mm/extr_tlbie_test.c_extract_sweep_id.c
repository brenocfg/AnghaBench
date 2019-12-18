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
 unsigned int SWEEP_ID_MASK ; 
 unsigned int SWEEP_ID_SHIFT ; 

__attribute__((used)) static inline unsigned int extract_sweep_id(unsigned int pattern)

{
	unsigned int ret;

	ret = (pattern >> SWEEP_ID_SHIFT) & SWEEP_ID_MASK;

	return ret;
}