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
typedef  int /*<<< orphan*/  mqtt_message_t ;
typedef  int /*<<< orphan*/  mqtt_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  MQTT_MSG_TYPE_SUBSCRIBE ; 
 int /*<<< orphan*/ * fini_message (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

mqtt_message_t* mqtt_msg_subscribe_fini(mqtt_connection_t* connection)
{
  return fini_message(connection, MQTT_MSG_TYPE_SUBSCRIBE, 0, 1, 0);
}