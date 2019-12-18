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
typedef  size_t uint64_t ;

/* Variables and functions */
 size_t random () ; 

__attribute__((used)) static void generate_random_array(uint64_t *guest_array, uint64_t size)
{
	uint64_t i;

	for (i = 0; i < size; i++)
		guest_array[i] = random();
}