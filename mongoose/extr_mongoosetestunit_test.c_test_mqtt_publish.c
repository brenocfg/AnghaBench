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
struct mg_mqtt_proto_data {int /*<<< orphan*/  last_control_time; } ;
struct TYPE_2__ {char* buf; char const len; } ;
struct mg_connection {scalar_t__ proto_data; TYPE_1__ send_mbuf; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (char const) ; 
 int /*<<< orphan*/  ASSERT_EQ (char const,int) ; 
 int /*<<< orphan*/  ASSERT_GT (int /*<<< orphan*/ ,double const) ; 
 int /*<<< orphan*/  ASSERT_STREQ_NZ (char const*,char*) ; 
 int MG_MQTT_CMD_PUBLISH ; 
 char const MG_MQTT_GET_QOS (char const) ; 
 char const MG_MQTT_QOS (int) ; 
 char const MG_MQTT_RETAIN ; 
 struct mg_connection* create_test_connection () ; 
 int /*<<< orphan*/  destroy_test_connection (struct mg_connection*) ; 
 int /*<<< orphan*/  mg_mqtt_publish (struct mg_connection*,char*,int,char const,char*,int) ; 
 int /*<<< orphan*/  mg_set_protocol_mqtt (struct mg_connection*) ; 
 double mg_time () ; 
 int /*<<< orphan*/  msleep (int) ; 
 char const strncmp (char const*,char*,int) ; 

__attribute__((used)) static const char *test_mqtt_publish(void) {
  struct mg_connection *nc = create_test_connection();
  const double before = mg_time();
  char data[] = "dummy";
  const char *got;

  mg_set_protocol_mqtt(nc);
  msleep(2);
  mg_mqtt_publish(nc, "/test", 42, MG_MQTT_QOS(1) | MG_MQTT_RETAIN, data,
                  sizeof(data));
  got = nc->send_mbuf.buf;
  ASSERT_EQ(nc->send_mbuf.len, 17);

  ASSERT(got[0] & MG_MQTT_RETAIN);
  ASSERT_EQ((got[0] & 0xf0), (MG_MQTT_CMD_PUBLISH << 4));
  ASSERT_EQ(MG_MQTT_GET_QOS(got[0]), 1);
  ASSERT_EQ((size_t) got[1], (nc->send_mbuf.len - 2));

  ASSERT_EQ(got[2], 0);
  ASSERT_EQ(got[3], 5);
  ASSERT_STREQ_NZ(&got[4], "/test");

  ASSERT_EQ(got[9], 0);
  ASSERT_EQ(got[10], 42);

  ASSERT_EQ(strncmp(&got[11], data, sizeof(data)), 0);

  ASSERT_GT(((struct mg_mqtt_proto_data *) nc->proto_data)->last_control_time,
            before);

  destroy_test_connection(nc);
  return NULL;
}