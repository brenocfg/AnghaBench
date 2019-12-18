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
struct unreachable_data {int /*<<< orphan*/  location; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  ubsan_epilogue (unsigned long*) ; 
 int /*<<< orphan*/  ubsan_prologue (int /*<<< orphan*/ *,unsigned long*) ; 

void __ubsan_handle_builtin_unreachable(struct unreachable_data *data)
{
	unsigned long flags;

	ubsan_prologue(&data->location, &flags);
	pr_err("calling __builtin_unreachable()\n");
	ubsan_epilogue(&flags);
	panic("can't return from __builtin_unreachable()");
}