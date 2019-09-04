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
struct dev_data {int /*<<< orphan*/  wait; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dev_data*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitqueue_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void put_dev (struct dev_data *data)
{
	if (likely (!refcount_dec_and_test (&data->count)))
		return;
	/* needs no more cleanup */
	BUG_ON (waitqueue_active (&data->wait));
	kfree (data);
}