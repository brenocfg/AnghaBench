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
struct ida {int dummy; } ;

/* Variables and functions */
 unsigned long ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IDA_BUG_ON (struct ida*,int) ; 
 unsigned long ida_alloc_min (struct ida*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_destroy (struct ida*) ; 
 int /*<<< orphan*/  ida_is_empty (struct ida*) ; 

__attribute__((used)) static void ida_check_max(struct ida *ida)
{
	unsigned long i, j;

	for (j = 1; j < 65537; j *= 2) {
		unsigned long base = (1UL << 31) - j;
		for (i = 0; i < j; i++) {
			IDA_BUG_ON(ida, ida_alloc_min(ida, base, GFP_KERNEL) !=
					base + i);
		}
		IDA_BUG_ON(ida, ida_alloc_min(ida, base, GFP_KERNEL) !=
				-ENOSPC);
		ida_destroy(ida);
		IDA_BUG_ON(ida, !ida_is_empty(ida));
	}
}