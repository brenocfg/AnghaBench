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
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  buffer_mutex ; 
 int /*<<< orphan*/  buffer_ready ; 
 int /*<<< orphan*/  buffer_wait ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void wake_up_buffer_waiter(void)
{
	mutex_lock(&buffer_mutex);
	atomic_set(&buffer_ready, 1);
	wake_up(&buffer_wait);
	mutex_unlock(&buffer_mutex);
}