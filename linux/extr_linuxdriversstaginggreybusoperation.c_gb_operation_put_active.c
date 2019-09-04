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
struct gb_operation {scalar_t__ active; int /*<<< orphan*/  waiters; int /*<<< orphan*/  links; struct gb_connection* connection; } ;
struct gb_connection {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gb_operation_cancellation_queue ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_gb_operation_put_active (struct gb_operation*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gb_operation_put_active(struct gb_operation *operation)
{
	struct gb_connection *connection = operation->connection;
	unsigned long flags;

	spin_lock_irqsave(&connection->lock, flags);

	trace_gb_operation_put_active(operation);

	if (--operation->active == 0) {
		list_del(&operation->links);
		if (atomic_read(&operation->waiters))
			wake_up(&gb_operation_cancellation_queue);
	}
	spin_unlock_irqrestore(&connection->lock, flags);
}