#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  buffer_length; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ mqtt_connection_t ;
typedef  int /*<<< orphan*/  connection ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void mqtt_msg_init(mqtt_connection_t* connection, uint8_t* buffer, uint16_t buffer_length)
{
  memset(connection, 0, sizeof(connection));
  connection->buffer = buffer;
  connection->buffer_length = buffer_length;
}