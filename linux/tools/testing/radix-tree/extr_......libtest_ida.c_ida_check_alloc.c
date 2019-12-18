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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IDA_BUG_ON (struct ida*,int) ; 
 int ida_alloc (struct ida*,int /*<<< orphan*/ ) ; 
 int ida_alloc_min (struct ida*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_destroy (struct ida*) ; 
 int /*<<< orphan*/  ida_free (struct ida*,int) ; 
 int /*<<< orphan*/  ida_is_empty (struct ida*) ; 

__attribute__((used)) static void ida_check_alloc(struct ida *ida)
{
	int i, id;

	for (i = 0; i < 10000; i++)
		IDA_BUG_ON(ida, ida_alloc(ida, GFP_KERNEL) != i);

	ida_free(ida, 20);
	ida_free(ida, 21);
	for (i = 0; i < 3; i++) {
		id = ida_alloc(ida, GFP_KERNEL);
		IDA_BUG_ON(ida, id < 0);
		if (i == 2)
			IDA_BUG_ON(ida, id != 10000);
	}

	for (i = 0; i < 5000; i++)
		ida_free(ida, i);

	IDA_BUG_ON(ida, ida_alloc_min(ida, 5000, GFP_KERNEL) != 10001);
	ida_destroy(ida);

	IDA_BUG_ON(ida, !ida_is_empty(ida));
}