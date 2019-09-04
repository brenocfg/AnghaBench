#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t len; } ;
struct mg_mqtt_message {TYPE_2__ payload; int /*<<< orphan*/  topic; } ;
struct TYPE_3__ {char* buf; } ;
struct mg_connection {TYPE_1__ recv_mbuf; scalar_t__ user_data; } ;

/* Variables and functions */
#define  MG_EV_MQTT_CONNACK 130 
#define  MG_EV_MQTT_PUBLISH 129 
#define  MG_EV_MQTT_SUBACK 128 
 int /*<<< orphan*/  mg_vcmp (int /*<<< orphan*/ *,char*) ; 
 size_t mqtt_long_payload_len ; 
 size_t mqtt_very_long_payload_len ; 

__attribute__((used)) static void mqtt_eh(struct mg_connection *nc, int ev, void *ev_data) {
  int *check = (int *) nc->user_data;
  struct mg_mqtt_message *mm = (struct mg_mqtt_message *) ev_data;
  size_t i;
  (void) nc;
  (void) ev_data;

  switch (ev) {
    case MG_EV_MQTT_SUBACK:
      *check = 1;
      break;
    case MG_EV_MQTT_PUBLISH:
      *check = 0;
      if (mg_vcmp(&mm->topic, "/topic")) {
        *check = -1;
        break;
      }

      for (i = 0; i < mm->payload.len; i++) {
        if (nc->recv_mbuf.buf[10 + i] != 'A') {
          *check = -1;
          break;
        }
      }

      if (mm->payload.len == mqtt_long_payload_len) {
        *check = 2;
      } else if (mm->payload.len == mqtt_very_long_payload_len) {
        *check = 3;
      }
      break;
    case MG_EV_MQTT_CONNACK:
      *check = 4;
      break;
  }
}