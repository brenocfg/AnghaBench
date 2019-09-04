#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int length; int* data; } ;
typedef  TYPE_1__ mqtt_message_t ;
struct TYPE_6__ {int* buffer; TYPE_1__ message; } ;
typedef  TYPE_2__ mqtt_connection_t ;

/* Variables and functions */
 int MQTT_MAX_FIXED_HEADER_SIZE ; 

__attribute__((used)) static mqtt_message_t* fini_message(mqtt_connection_t* connection, int type, int dup, int qos, int retain)
{
  int remaining_length = connection->message.length - MQTT_MAX_FIXED_HEADER_SIZE;

  if(remaining_length > 127)
  {
    connection->buffer[0] = ((type & 0x0f) << 4) | ((dup & 1) << 3) | ((qos & 3) << 1) | (retain & 1);
    connection->buffer[1] = 0x80 | (remaining_length % 128);
    connection->buffer[2] = remaining_length / 128;
    connection->message.length = remaining_length + 3;
    connection->message.data = connection->buffer;
  }
  else
  {
    connection->buffer[1] = ((type & 0x0f) << 4) | ((dup & 1) << 3) | ((qos & 3) << 1) | (retain & 1);
    connection->buffer[2] = remaining_length;
    connection->message.length = remaining_length + 2;
    connection->message.data = connection->buffer + 1;
  }

  return &connection->message;
}