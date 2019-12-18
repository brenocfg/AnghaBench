#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ length; } ;
typedef  TYPE_1__ mqtt_message_t ;
struct TYPE_9__ {scalar_t__ buffer_length; int* buffer; TYPE_1__ message; } ;
typedef  TYPE_2__ mqtt_connection_t ;

/* Variables and functions */
 scalar_t__ append_string (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* fail_message (TYPE_2__*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

mqtt_message_t* mqtt_msg_subscribe_topic(mqtt_connection_t* connection, const char* topic, int qos)
{
  if(topic == NULL || topic[0] == '\0')
    return fail_message(connection);

  if(append_string(connection, topic, strlen(topic)) < 0)
    return fail_message(connection);

  if(connection->message.length + 1 > connection->buffer_length)
    return fail_message(connection);
  connection->buffer[connection->message.length++] = qos;

  return &connection->message;
}