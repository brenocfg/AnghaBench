#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  unit; } ;
struct cmp_connection {int connected; scalar_t__ direction; int /*<<< orphan*/  mutex; TYPE_2__ resources; int /*<<< orphan*/  speed; int /*<<< orphan*/  max_speed; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_ON_BUS_RESET ; 
 scalar_t__ CMP_OUTPUT ; 
 int EAGAIN ; 
 int EISCONN ; 
 scalar_t__ WARN_ON (int) ; 
 int fw_iso_resources_allocate (TYPE_2__*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_iso_resources_free (TYPE_2__*) ; 
 TYPE_1__* fw_parent_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipcr_set_modify ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opcr_set_modify ; 
 int pcr_modify (struct cmp_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcr_set_check ; 

int cmp_connection_establish(struct cmp_connection *c,
			     unsigned int max_payload_bytes)
{
	int err;

	if (WARN_ON(c->connected))
		return -EISCONN;

	c->speed = min(c->max_speed,
		       fw_parent_device(c->resources.unit)->max_speed);

	mutex_lock(&c->mutex);

retry_after_bus_reset:
	err = fw_iso_resources_allocate(&c->resources,
					max_payload_bytes, c->speed);
	if (err < 0)
		goto err_mutex;

	if (c->direction == CMP_OUTPUT)
		err = pcr_modify(c, opcr_set_modify, pcr_set_check,
				 ABORT_ON_BUS_RESET);
	else
		err = pcr_modify(c, ipcr_set_modify, pcr_set_check,
				 ABORT_ON_BUS_RESET);

	if (err == -EAGAIN) {
		fw_iso_resources_free(&c->resources);
		goto retry_after_bus_reset;
	}
	if (err < 0)
		goto err_resources;

	c->connected = true;

	mutex_unlock(&c->mutex);

	return 0;

err_resources:
	fw_iso_resources_free(&c->resources);
err_mutex:
	mutex_unlock(&c->mutex);

	return err;
}