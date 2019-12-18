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
struct test_parman {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct test_parman*) ; 
 int PTR_ERR (struct test_parman*) ; 
 int test_parman_check_array (struct test_parman*,int) ; 
 struct test_parman* test_parman_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_parman_destroy (struct test_parman*) ; 
 int /*<<< orphan*/  test_parman_lsort_ops ; 
 int test_parman_run (struct test_parman*) ; 

__attribute__((used)) static int test_parman_lsort(void)
{
	struct test_parman *test_parman;
	int err;

	test_parman = test_parman_create(&test_parman_lsort_ops);
	if (IS_ERR(test_parman))
		return PTR_ERR(test_parman);

	err = test_parman_run(test_parman);
	if (err)
		goto out;

	err = test_parman_check_array(test_parman, false);
	if (err)
		goto out;
out:
	test_parman_destroy(test_parman);
	return err;
}