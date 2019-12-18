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
 int /*<<< orphan*/  IDA_BUG_ON (struct ida*,int) ; 
 int /*<<< orphan*/  ida_check_destroy_1 (struct ida*,int) ; 
 int /*<<< orphan*/  ida_destroy (struct ida*) ; 
 int /*<<< orphan*/  ida_is_empty (struct ida*) ; 

__attribute__((used)) static void ida_check_destroy(struct ida *ida)
{
	/* Destroy an already-empty IDA */
	IDA_BUG_ON(ida, !ida_is_empty(ida));
	ida_destroy(ida);
	IDA_BUG_ON(ida, !ida_is_empty(ida));

	ida_check_destroy_1(ida, 0);
	ida_check_destroy_1(ida, 1);
	ida_check_destroy_1(ida, 1023);
	ida_check_destroy_1(ida, 1024);
	ida_check_destroy_1(ida, 12345678);
}