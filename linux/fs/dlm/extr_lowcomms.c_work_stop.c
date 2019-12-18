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
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 scalar_t__ recv_workqueue ; 
 scalar_t__ send_workqueue ; 

__attribute__((used)) static void work_stop(void)
{
	if (recv_workqueue)
		destroy_workqueue(recv_workqueue);
	if (send_workqueue)
		destroy_workqueue(send_workqueue);
}