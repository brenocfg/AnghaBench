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
struct mg_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_MQTT_CMD_DISCONNECT ; 
 int /*<<< orphan*/  mg_send_mqtt_header (struct mg_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mg_mqtt_disconnect(struct mg_connection *nc) {
  mg_send_mqtt_header(nc, MG_MQTT_CMD_DISCONNECT, 0, 0);
}