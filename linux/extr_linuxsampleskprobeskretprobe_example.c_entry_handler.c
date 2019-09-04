#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct my_data {int /*<<< orphan*/  entry_stamp; } ;
struct kretprobe_instance {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static int entry_handler(struct kretprobe_instance *ri, struct pt_regs *regs)
{
	struct my_data *data;

	if (!current->mm)
		return 1;	/* Skip kernel threads */

	data = (struct my_data *)ri->data;
	data->entry_stamp = ktime_get();
	return 0;
}