#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  unit; int /*<<< orphan*/  allocated; } ;
struct cmp_connection {int /*<<< orphan*/  mutex; int /*<<< orphan*/  speed; TYPE_2__ resources; int /*<<< orphan*/  max_speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_speed; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int fw_iso_resources_allocate (TYPE_2__*,unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* fw_parent_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int cmp_connection_reserve(struct cmp_connection *c,
			   unsigned int max_payload_bytes)
{
	int err;

	mutex_lock(&c->mutex);

	if (WARN_ON(c->resources.allocated)) {
		err = -EBUSY;
		goto end;
	}

	c->speed = min(c->max_speed,
		       fw_parent_device(c->resources.unit)->max_speed);

	err = fw_iso_resources_allocate(&c->resources, max_payload_bytes,
					c->speed);
end:
	mutex_unlock(&c->mutex);

	return err;
}