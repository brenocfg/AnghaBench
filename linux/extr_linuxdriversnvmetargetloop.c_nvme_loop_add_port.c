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
struct nvmet_port {int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_loop_ports ; 
 int /*<<< orphan*/  nvme_loop_ports_mutex ; 

__attribute__((used)) static int nvme_loop_add_port(struct nvmet_port *port)
{
	mutex_lock(&nvme_loop_ports_mutex);
	list_add_tail(&port->entry, &nvme_loop_ports);
	mutex_unlock(&nvme_loop_ports_mutex);
	return 0;
}