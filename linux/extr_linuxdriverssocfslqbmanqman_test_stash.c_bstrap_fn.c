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
struct bstrap {int (* fn ) () ;int /*<<< orphan*/  started; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 () ; 

__attribute__((used)) static int bstrap_fn(void *bs)
{
	struct bstrap *bstrap = bs;
	int err;

	atomic_inc(&bstrap->started);
	err = bstrap->fn();
	if (err)
		return err;
	while (!kthread_should_stop())
		msleep(20);
	return 0;
}