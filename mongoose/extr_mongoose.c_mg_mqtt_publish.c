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
typedef  int uint16_t ;
struct mg_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MG_MQTT_CMD_PUBLISH ; 
 scalar_t__ MG_MQTT_GET_QOS (int) ; 
 int htons (int) ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,void const*,size_t) ; 
 int /*<<< orphan*/  mg_send_mqtt_header (struct mg_connection*,int /*<<< orphan*/ ,int,size_t) ; 
 int strlen (char const*) ; 

void mg_mqtt_publish(struct mg_connection *nc, const char *topic,
                     uint16_t message_id, int flags, const void *data,
                     size_t len) {
  uint16_t netbytes;
  uint16_t topic_len = strlen(topic);

  size_t total_len = 2 + topic_len + len;
  if (MG_MQTT_GET_QOS(flags) > 0) {
    total_len += 2;
  }

  mg_send_mqtt_header(nc, MG_MQTT_CMD_PUBLISH, flags, total_len);

  netbytes = htons(topic_len);
  mg_send(nc, &netbytes, 2);
  mg_send(nc, topic, topic_len);

  if (MG_MQTT_GET_QOS(flags) > 0) {
    netbytes = htons(message_id);
    mg_send(nc, &netbytes, 2);
  }

  mg_send(nc, data, len);
}