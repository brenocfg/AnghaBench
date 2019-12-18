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
 int /*<<< orphan*/  WWL1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WWU (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o ; 

__attribute__((used)) static void ww_test_object_unlock_twice(void)
{
	WWL1(&o);
	WWU(&o);
	WWU(&o);
}