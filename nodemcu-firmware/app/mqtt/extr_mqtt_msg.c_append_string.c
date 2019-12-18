#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ length; } ;
struct TYPE_5__ {scalar_t__ buffer_length; int* buffer; TYPE_1__ message; } ;
typedef  TYPE_2__ mqtt_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,char const*,int) ; 

__attribute__((used)) static int append_string(mqtt_connection_t* connection, const char* string, int len)
{
  if(connection->message.length + len + 2 > connection->buffer_length)
    return -1;

  connection->buffer[connection->message.length++] = len >> 8;
  connection->buffer[connection->message.length++] = len & 0xff;
  memcpy(connection->buffer + connection->message.length, string, len);
  connection->message.length += len;

  return len + 2;
}