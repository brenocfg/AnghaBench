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
struct flex_array {int element_size; int total_nr_elements; } ;

/* Variables and functions */
 int FLEX_ARRAY_BASE_BYTES_LEFT ; 

__attribute__((used)) static inline int elements_fit_in_base(struct flex_array *fa)
{
	int data_size = fa->element_size * fa->total_nr_elements;
	if (data_size <= FLEX_ARRAY_BASE_BYTES_LEFT)
		return 1;
	return 0;
}