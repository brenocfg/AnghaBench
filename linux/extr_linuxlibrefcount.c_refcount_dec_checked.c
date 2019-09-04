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
 int /*<<< orphan*/  WARN_ONCE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  refcount_dec_and_test_checked (int /*<<< orphan*/ *) ; 

void refcount_dec_checked(refcount_t *r)
{
	WARN_ONCE(refcount_dec_and_test_checked(r), "refcount_t: decrement hit 0; leaking memory.\n");
}