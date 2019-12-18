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
typedef  int /*<<< orphan*/  wait_queue_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  hidp_session_wq ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hidp_session_wake_function(wait_queue_entry_t *wait,
				      unsigned int mode,
				      int sync, void *key)
{
	wake_up_interruptible(&hidp_session_wq);
	return false;
}