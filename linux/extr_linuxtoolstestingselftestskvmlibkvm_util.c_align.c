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
 int /*<<< orphan*/  TEST_ASSERT (int,char*,size_t) ; 

__attribute__((used)) static void *align(void *x, size_t size)
{
	size_t mask = size - 1;
	TEST_ASSERT(size != 0 && !(size & (size - 1)),
		    "size not a power of 2: %lu", size);
	return (void *) (((size_t) x + mask) & ~mask);
}