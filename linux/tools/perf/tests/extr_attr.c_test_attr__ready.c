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
 int ready ; 
 int /*<<< orphan*/  test_attr__enabled ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void test_attr__ready(void)
{
	if (unlikely(test_attr__enabled) && !ready)
		ready = true;
}