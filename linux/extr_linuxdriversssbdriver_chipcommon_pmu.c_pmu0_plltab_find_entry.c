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
typedef  scalar_t__ u32 ;
struct pmu0_plltab_entry {scalar_t__ freq; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct pmu0_plltab_entry*) ; 
 struct pmu0_plltab_entry* pmu0_plltab ; 

__attribute__((used)) static const struct pmu0_plltab_entry * pmu0_plltab_find_entry(u32 crystalfreq)
{
	const struct pmu0_plltab_entry *e;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(pmu0_plltab); i++) {
		e = &pmu0_plltab[i];
		if (e->freq == crystalfreq)
			return e;
	}

	return NULL;
}