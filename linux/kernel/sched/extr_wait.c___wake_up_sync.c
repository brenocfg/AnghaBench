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
 int /*<<< orphan*/  __wake_up_sync_key (struct wait_queue_head*,unsigned int,int,int /*<<< orphan*/ *) ; 

void __wake_up_sync(struct wait_queue_head *wq_head, unsigned int mode, int nr_exclusive)
{
	__wake_up_sync_key(wq_head, mode, nr_exclusive, NULL);
}