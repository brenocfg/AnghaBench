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
 unsigned int ida_alloc_min (struct ida*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_destroy (struct ida*) ; 
 int ida_is_empty (struct ida*) ; 

__attribute__((used)) static void ida_check_destroy_1(struct ida *ida, unsigned int base)
{
	IDA_BUG_ON(ida, ida_alloc_min(ida, base, GFP_KERNEL) != base);
	IDA_BUG_ON(ida, ida_is_empty(ida));
	ida_destroy(ida);
	IDA_BUG_ON(ida, !ida_is_empty(ida));
}