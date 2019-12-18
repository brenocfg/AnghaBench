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
struct pstack {unsigned short max_nr_entries; } ;

/* Variables and functions */
 struct pstack* zalloc (int) ; 

struct pstack *pstack__new(unsigned short max_nr_entries)
{
	struct pstack *pstack = zalloc((sizeof(*pstack) +
				       max_nr_entries * sizeof(void *)));
	if (pstack != NULL)
		pstack->max_nr_entries = max_nr_entries;
	return pstack;
}