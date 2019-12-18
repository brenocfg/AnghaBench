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
struct cmp_connection {int connected; scalar_t__ direction; int /*<<< orphan*/  mutex; int /*<<< orphan*/  resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_ON_BUS_RESET ; 
 scalar_t__ CMP_OUTPUT ; 
 int EAGAIN ; 
 int EISCONN ; 
 scalar_t__ WARN_ON (int) ; 
 int fw_iso_resources_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipcr_set_modify ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opcr_set_modify ; 
 int pcr_modify (struct cmp_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcr_set_check ; 

int cmp_connection_establish(struct cmp_connection *c)
{
	int err;

	mutex_lock(&c->mutex);

	if (WARN_ON(c->connected)) {
		mutex_unlock(&c->mutex);
		return -EISCONN;
	}

retry_after_bus_reset:
	if (c->direction == CMP_OUTPUT)
		err = pcr_modify(c, opcr_set_modify, pcr_set_check,
				 ABORT_ON_BUS_RESET);
	else
		err = pcr_modify(c, ipcr_set_modify, pcr_set_check,
				 ABORT_ON_BUS_RESET);

	if (err == -EAGAIN) {
		err = fw_iso_resources_update(&c->resources);
		if (err >= 0)
			goto retry_after_bus_reset;
	}
	if (err >= 0)
		c->connected = true;

	mutex_unlock(&c->mutex);

	return err;
}