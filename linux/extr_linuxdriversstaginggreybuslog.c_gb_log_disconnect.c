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
struct gb_log {struct gb_connection* connection; } ;
struct gb_connection {int dummy; } ;
struct gb_bundle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_connection_destroy (struct gb_connection*) ; 
 int /*<<< orphan*/  gb_connection_disable (struct gb_connection*) ; 
 struct gb_log* greybus_get_drvdata (struct gb_bundle*) ; 
 int /*<<< orphan*/  kfree (struct gb_log*) ; 

__attribute__((used)) static void gb_log_disconnect(struct gb_bundle *bundle)
{
	struct gb_log *log = greybus_get_drvdata(bundle);
	struct gb_connection *connection = log->connection;

	gb_connection_disable(connection);
	gb_connection_destroy(connection);

	kfree(log);
}