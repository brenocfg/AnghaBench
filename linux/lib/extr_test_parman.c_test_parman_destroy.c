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
struct test_parman {int /*<<< orphan*/  parman; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct test_parman*) ; 
 int /*<<< orphan*/  parman_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_parman_items_fini (struct test_parman*) ; 
 int /*<<< orphan*/  test_parman_prios_fini (struct test_parman*) ; 
 int /*<<< orphan*/  test_parman_resize (struct test_parman*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_parman_destroy(struct test_parman *test_parman)
{
	test_parman_items_fini(test_parman);
	test_parman_prios_fini(test_parman);
	parman_destroy(test_parman->parman);
	test_parman_resize(test_parman, 0);
	kfree(test_parman);
}