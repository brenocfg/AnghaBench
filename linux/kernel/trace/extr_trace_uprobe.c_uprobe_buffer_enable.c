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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  event_mutex ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int uprobe_buffer_init () ; 
 int /*<<< orphan*/  uprobe_buffer_refcnt ; 

__attribute__((used)) static int uprobe_buffer_enable(void)
{
	int ret = 0;

	BUG_ON(!mutex_is_locked(&event_mutex));

	if (uprobe_buffer_refcnt++ == 0) {
		ret = uprobe_buffer_init();
		if (ret < 0)
			uprobe_buffer_refcnt--;
	}

	return ret;
}