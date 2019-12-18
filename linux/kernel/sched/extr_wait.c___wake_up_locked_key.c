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
struct wait_queue_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __wake_up_common (struct wait_queue_head*,unsigned int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

void __wake_up_locked_key(struct wait_queue_head *wq_head, unsigned int mode, void *key)
{
	__wake_up_common(wq_head, mode, 1, 0, key, NULL);
}