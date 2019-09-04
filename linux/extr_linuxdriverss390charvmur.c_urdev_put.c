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
struct urdev {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  urdev_free (struct urdev*) ; 

__attribute__((used)) static void urdev_put(struct urdev *urd)
{
	if (refcount_dec_and_test(&urd->ref_count))
		urdev_free(urd);
}