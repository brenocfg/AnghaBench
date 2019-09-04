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
struct gb_connection {scalar_t__ state; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ GB_CONNECTION_STATE_ENABLED ; 
 scalar_t__ GB_CONNECTION_STATE_ENABLED_TX ; 
 int _gb_connection_enable (struct gb_connection*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_gb_connection_enable (struct gb_connection*) ; 

int gb_connection_enable_tx(struct gb_connection *connection)
{
	int ret = 0;

	mutex_lock(&connection->mutex);

	if (connection->state == GB_CONNECTION_STATE_ENABLED) {
		ret = -EINVAL;
		goto out_unlock;
	}

	if (connection->state == GB_CONNECTION_STATE_ENABLED_TX)
		goto out_unlock;

	ret = _gb_connection_enable(connection, false);
	if (!ret)
		trace_gb_connection_enable(connection);

out_unlock:
	mutex_unlock(&connection->mutex);

	return ret;
}