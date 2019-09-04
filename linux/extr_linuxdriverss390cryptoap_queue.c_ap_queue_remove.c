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
struct ap_queue {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ap_flush_queue (struct ap_queue*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

void ap_queue_remove(struct ap_queue *aq)
{
	ap_flush_queue(aq);
	del_timer_sync(&aq->timeout);
}