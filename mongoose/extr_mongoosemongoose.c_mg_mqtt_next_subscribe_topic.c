#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned char uint8_t ;
struct mg_str {unsigned char len; char* p; } ;
struct TYPE_2__ {size_t len; scalar_t__ p; } ;
struct mg_mqtt_message {TYPE_1__ payload; } ;

/* Variables and functions */

int mg_mqtt_next_subscribe_topic(struct mg_mqtt_message *msg,
                                 struct mg_str *topic, uint8_t *qos, int pos) {
  unsigned char *buf = (unsigned char *) msg->payload.p + pos;
  int new_pos;

  if ((size_t) pos >= msg->payload.len) return -1;

  topic->len = buf[0] << 8 | buf[1];
  topic->p = (char *) buf + 2;
  new_pos = pos + 2 + topic->len + 1;
  if ((size_t) new_pos > msg->payload.len) return -1;
  *qos = buf[2 + topic->len];
  return new_pos;
}