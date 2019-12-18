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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  huge_zero_refcount ; 

__attribute__((used)) static void put_huge_zero_page(void)
{
	/*
	 * Counter should never go to zero here. Only shrinker can put
	 * last reference.
	 */
	BUG_ON(atomic_dec_and_test(&huge_zero_refcount));
}