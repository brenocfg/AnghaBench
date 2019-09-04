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
struct tb_protocol_handler {int /*<<< orphan*/  list; int /*<<< orphan*/  uuid; int /*<<< orphan*/  callback; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  protocol_handlers ; 
 int /*<<< orphan*/  tb_xdp_uuid ; 
 scalar_t__ uuid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdomain_lock ; 

int tb_register_protocol_handler(struct tb_protocol_handler *handler)
{
	if (!handler->uuid || !handler->callback)
		return -EINVAL;
	if (uuid_equal(handler->uuid, &tb_xdp_uuid))
		return -EINVAL;

	mutex_lock(&xdomain_lock);
	list_add_tail(&handler->list, &protocol_handlers);
	mutex_unlock(&xdomain_lock);

	return 0;
}