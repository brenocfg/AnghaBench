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
 int /*<<< orphan*/  DEFINE_IDA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ida ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int ida_is_empty (int /*<<< orphan*/ *) ; 
 unsigned long ida_simple_get (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,unsigned long) ; 

void ida_simple_get_remove_test(void)
{
	DEFINE_IDA(ida);
	unsigned long i;

	for (i = 0; i < 10000; i++) {
		assert(ida_simple_get(&ida, 0, 20000, GFP_KERNEL) == i);
	}
	assert(ida_simple_get(&ida, 5, 30, GFP_KERNEL) < 0);

	for (i = 0; i < 10000; i++) {
		ida_simple_remove(&ida, i);
	}
	assert(ida_is_empty(&ida));

	ida_destroy(&ida);
}