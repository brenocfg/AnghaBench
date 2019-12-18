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
 int FIXED_1 ; 
 int FSHIFT ; 

__attribute__((used)) static inline unsigned long fixed_loadavg(int load)
{
	int rnd_load = load + (FIXED_1/200);
	int rnd_frac = ((rnd_load & (FIXED_1-1)) * 100) >> FSHIFT;

	return ((rnd_load >> FSHIFT) * 100) + rnd_frac;
}