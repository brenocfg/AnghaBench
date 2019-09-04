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
struct gb_operation {int active; struct gb_connection* connection; } ;
struct gb_connection {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool gb_operation_is_active(struct gb_operation *operation)
{
	struct gb_connection *connection = operation->connection;
	unsigned long flags;
	bool ret;

	spin_lock_irqsave(&connection->lock, flags);
	ret = operation->active;
	spin_unlock_irqrestore(&connection->lock, flags);

	return ret;
}