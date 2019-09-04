#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ remove; scalar_t__ remote_notify; scalar_t__ process; scalar_t__ remote_insert; scalar_t__ local_insert; } ;
typedef  TYPE_1__ VCHIQ_BULK_QUEUE_T ;

/* Variables and functions */

__attribute__((used)) static void
init_bulk_queue(VCHIQ_BULK_QUEUE_T *queue)
{
	queue->local_insert = 0;
	queue->remote_insert = 0;
	queue->process = 0;
	queue->remote_notify = 0;
	queue->remove = 0;
}