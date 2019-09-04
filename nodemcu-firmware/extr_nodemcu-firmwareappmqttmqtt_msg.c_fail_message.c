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
struct TYPE_5__ {scalar_t__ length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ mqtt_message_t ;
struct TYPE_6__ {TYPE_1__ message; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_2__ mqtt_connection_t ;

/* Variables and functions */

__attribute__((used)) static mqtt_message_t* fail_message(mqtt_connection_t* connection)
{
  connection->message.data = connection->buffer;
  connection->message.length = 0;
  return &connection->message;
}