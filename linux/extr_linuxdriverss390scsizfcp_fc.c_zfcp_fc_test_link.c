#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct zfcp_port {int /*<<< orphan*/  dev; int /*<<< orphan*/  test_link_work; TYPE_1__* adapter; } ;
struct TYPE_2__ {int /*<<< orphan*/  work_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void zfcp_fc_test_link(struct zfcp_port *port)
{
	get_device(&port->dev);
	if (!queue_work(port->adapter->work_queue, &port->test_link_work))
		put_device(&port->dev);
}