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
struct flex_array {int dummy; } ;

/* Variables and functions */
 void** flex_array_get (struct flex_array*,unsigned int) ; 

void *flex_array_get_ptr(struct flex_array *fa, unsigned int element_nr)
{
	void **tmp;

	tmp = flex_array_get(fa, element_nr);
	if (!tmp)
		return NULL;

	return *tmp;
}