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
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WWL1 (int /*<<< orphan*/ *) ; 
 int WWT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WWU (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o ; 
 int /*<<< orphan*/  o2 ; 

__attribute__((used)) static void ww_test_try_block(void)
{
	bool ret;

	ret = WWT(&o);
	WARN_ON(!ret);

	WWL1(&o2);
	WWU(&o2);
	WWU(&o);
}