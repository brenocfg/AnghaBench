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
struct flex_array {int /*<<< orphan*/ * parts; } ;

/* Variables and functions */
 int FLEX_ARRAY_NR_BASE_PTRS ; 
 scalar_t__ elements_fit_in_base (struct flex_array*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void flex_array_free_parts(struct flex_array *fa)
{
	int part_nr;

	if (elements_fit_in_base(fa))
		return;
	for (part_nr = 0; part_nr < FLEX_ARRAY_NR_BASE_PTRS; part_nr++)
		kfree(fa->parts[part_nr]);
}