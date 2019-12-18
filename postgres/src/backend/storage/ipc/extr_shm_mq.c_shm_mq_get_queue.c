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
struct TYPE_3__ {int /*<<< orphan*/ * mqh_queue; } ;
typedef  TYPE_1__ shm_mq_handle ;
typedef  int /*<<< orphan*/  shm_mq ;

/* Variables and functions */

shm_mq *
shm_mq_get_queue(shm_mq_handle *mqh)
{
	return mqh->mqh_queue;
}