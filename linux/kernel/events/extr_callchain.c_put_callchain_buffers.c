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
 scalar_t__ atomic_dec_and_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callchain_mutex ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nr_callchain_events ; 
 int /*<<< orphan*/  release_callchain_buffers () ; 

void put_callchain_buffers(void)
{
	if (atomic_dec_and_mutex_lock(&nr_callchain_events, &callchain_mutex)) {
		release_callchain_buffers();
		mutex_unlock(&callchain_mutex);
	}
}