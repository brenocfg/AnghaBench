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
 int __pcpu_size_to_slot (int) ; 
 int pcpu_nr_slots ; 
 int pcpu_unit_size ; 

__attribute__((used)) static int pcpu_size_to_slot(int size)
{
	if (size == pcpu_unit_size)
		return pcpu_nr_slots - 1;
	return __pcpu_size_to_slot(size);
}