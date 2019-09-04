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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  binder_transfer_binder ; 
 int call_int_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct task_struct*,struct task_struct*) ; 

int security_binder_transfer_binder(struct task_struct *from,
				    struct task_struct *to)
{
	return call_int_hook(binder_transfer_binder, 0, from, to);
}