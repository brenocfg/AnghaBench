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
struct gb_connection {scalar_t__ state; int /*<<< orphan*/  hd_cport_id; int /*<<< orphan*/  hd; int /*<<< orphan*/  wq; int /*<<< orphan*/  hd_links; int /*<<< orphan*/  bundle_links; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPORT_ID_BAD ; 
 scalar_t__ GB_CONNECTION_STATE_DISABLED ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_mutex ; 
 int /*<<< orphan*/  gb_connection_put (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connections_lock ; 
 int /*<<< orphan*/  gb_hd_cport_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void gb_connection_destroy(struct gb_connection *connection)
{
	if (!connection)
		return;

	if (WARN_ON(connection->state != GB_CONNECTION_STATE_DISABLED))
		gb_connection_disable(connection);

	mutex_lock(&gb_connection_mutex);

	spin_lock_irq(&gb_connections_lock);
	list_del(&connection->bundle_links);
	list_del(&connection->hd_links);
	spin_unlock_irq(&gb_connections_lock);

	destroy_workqueue(connection->wq);

	gb_hd_cport_release(connection->hd, connection->hd_cport_id);
	connection->hd_cport_id = CPORT_ID_BAD;

	mutex_unlock(&gb_connection_mutex);

	gb_connection_put(connection);
}