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
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  r (void const*) ; 

__attribute__((used)) static int compare_relative_table(const void *a, const void *b)
{
	int32_t av = (int32_t)r(a);
	int32_t bv = (int32_t)r(b);

	if (av < bv)
		return -1;
	if (av > bv)
		return 1;
	return 0;
}