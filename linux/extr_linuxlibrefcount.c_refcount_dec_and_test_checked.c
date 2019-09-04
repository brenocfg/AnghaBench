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
typedef  int /*<<< orphan*/  refcount_t ;

/* Variables and functions */
 int refcount_sub_and_test_checked (int,int /*<<< orphan*/ *) ; 

bool refcount_dec_and_test_checked(refcount_t *r)
{
	return refcount_sub_and_test_checked(1, r);
}