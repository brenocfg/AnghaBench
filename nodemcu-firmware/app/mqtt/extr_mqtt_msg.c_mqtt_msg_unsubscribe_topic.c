#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mqtt_message_t ;
struct TYPE_5__ {int /*<<< orphan*/  message; } ;
typedef  TYPE_1__ mqtt_connection_t ;

/* Variables and functions */
 scalar_t__ append_string (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fail_message (TYPE_1__*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

mqtt_message_t* mqtt_msg_unsubscribe_topic(mqtt_connection_t* connection, const char* topic)
{
  if(topic == NULL || topic[0] == '\0')
    return fail_message(connection);

  if(append_string(connection, topic, strlen(topic)) < 0)
    return fail_message(connection);

  return &connection->message;
}