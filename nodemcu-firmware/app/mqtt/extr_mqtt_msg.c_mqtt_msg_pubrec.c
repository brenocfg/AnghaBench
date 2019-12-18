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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  mqtt_message_t ;
typedef  int /*<<< orphan*/  mqtt_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  MQTT_MSG_TYPE_PUBREC ; 
 scalar_t__ append_message_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fail_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fini_message (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_message (int /*<<< orphan*/ *) ; 

mqtt_message_t* mqtt_msg_pubrec(mqtt_connection_t* connection, uint16_t message_id)
{
  init_message(connection);
  if(append_message_id(connection, message_id) == 0)
    return fail_message(connection);
  return fini_message(connection, MQTT_MSG_TYPE_PUBREC, 0, 0, 0);
}