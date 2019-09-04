#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  mqtt_message_t ;
struct TYPE_6__ {int /*<<< orphan*/  message; } ;
typedef  TYPE_1__ mqtt_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  append_message_id (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fail_message (TYPE_1__*) ; 
 int /*<<< orphan*/  init_message (TYPE_1__*) ; 

mqtt_message_t* mqtt_msg_subscribe_init(mqtt_connection_t* connection, uint16_t *message_id)
{
  init_message(connection);

  if((*message_id = append_message_id(connection, 0)) == 0)
    return fail_message(connection);

  return &connection->message;
}