#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gb_message {TYPE_1__* operation; } ;
struct gb_connection {int /*<<< orphan*/  hd_cport_id; TYPE_3__* hd; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_6__ {TYPE_2__* driver; } ;
struct TYPE_5__ {int (* message_send ) (TYPE_3__*,int /*<<< orphan*/ ,struct gb_message*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {struct gb_connection* connection; } ;

/* Variables and functions */
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ,struct gb_message*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_gb_message_send (struct gb_message*) ; 

__attribute__((used)) static int gb_message_send(struct gb_message *message, gfp_t gfp)
{
	struct gb_connection *connection = message->operation->connection;

	trace_gb_message_send(message);
	return connection->hd->driver->message_send(connection->hd,
					connection->hd_cport_id,
					message,
					gfp);
}