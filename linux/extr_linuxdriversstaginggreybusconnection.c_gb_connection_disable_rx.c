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
struct gb_connection {scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESHUTDOWN ; 
 scalar_t__ GB_CONNECTION_STATE_ENABLED ; 
 scalar_t__ GB_CONNECTION_STATE_ENABLED_TX ; 
 int /*<<< orphan*/  gb_connection_flush_incoming_operations (struct gb_connection*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_gb_connection_disable (struct gb_connection*) ; 

void gb_connection_disable_rx(struct gb_connection *connection)
{
	mutex_lock(&connection->mutex);

	spin_lock_irq(&connection->lock);
	if (connection->state != GB_CONNECTION_STATE_ENABLED) {
		spin_unlock_irq(&connection->lock);
		goto out_unlock;
	}
	connection->state = GB_CONNECTION_STATE_ENABLED_TX;
	gb_connection_flush_incoming_operations(connection, -ESHUTDOWN);
	spin_unlock_irq(&connection->lock);

	trace_gb_connection_disable(connection);

out_unlock:
	mutex_unlock(&connection->mutex);
}