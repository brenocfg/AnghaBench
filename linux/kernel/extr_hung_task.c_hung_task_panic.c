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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int did_panic ; 

__attribute__((used)) static int
hung_task_panic(struct notifier_block *this, unsigned long event, void *ptr)
{
	did_panic = 1;

	return NOTIFY_DONE;
}