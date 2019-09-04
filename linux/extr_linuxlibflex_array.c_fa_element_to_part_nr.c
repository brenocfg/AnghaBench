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
struct flex_array {int /*<<< orphan*/  reciprocal_elems; } ;

/* Variables and functions */
 int reciprocal_divide (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fa_element_to_part_nr(struct flex_array *fa,
					unsigned int element_nr)
{
	/*
	 * if element_size == 0 we don't get here, so we never touch
	 * the zeroed fa->reciprocal_elems, which would yield invalid
	 * results
	 */
	return reciprocal_divide(element_nr, fa->reciprocal_elems);
}