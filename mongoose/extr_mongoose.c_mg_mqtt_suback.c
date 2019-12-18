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
typedef  int /*<<< orphan*/  uint16_t ;
struct mg_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_MQTT_CMD_SUBACK ; 
 int /*<<< orphan*/  MG_MQTT_QOS (int) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mg_send_mqtt_header (struct mg_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void mg_mqtt_suback(struct mg_connection *nc, uint8_t *qoss, size_t qoss_len,
                    uint16_t message_id) {
  size_t i;
  uint16_t netbytes;

  mg_send_mqtt_header(nc, MG_MQTT_CMD_SUBACK, MG_MQTT_QOS(1), 2 + qoss_len);

  netbytes = htons(message_id);
  mg_send(nc, &netbytes, 2);

  for (i = 0; i < qoss_len; i++) {
    mg_send(nc, &qoss[i], 1);
  }
}