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
typedef  int /*<<< orphan*/  uint8_t ;
struct mg_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_MQTT_CMD_CONNACK ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mg_send_mqtt_header (struct mg_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void mg_mqtt_connack(struct mg_connection *nc, uint8_t return_code) {
  uint8_t unused = 0;
  mg_send_mqtt_header(nc, MG_MQTT_CMD_CONNACK, 0, 2);
  mg_send(nc, &unused, 1);
  mg_send(nc, &return_code, 1);
}