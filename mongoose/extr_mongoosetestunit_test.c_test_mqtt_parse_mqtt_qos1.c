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
struct TYPE_4__ {int /*<<< orphan*/  p; int /*<<< orphan*/  len; } ;
struct TYPE_3__ {int /*<<< orphan*/  p; int /*<<< orphan*/  len; } ;
struct mg_mqtt_message {TYPE_2__ payload; TYPE_1__ topic; int /*<<< orphan*/  message_id; int /*<<< orphan*/  qos; int /*<<< orphan*/  cmd; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  msg_qos1 ;
typedef  int /*<<< orphan*/  mm ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ASSERT_STREQ_NZ (int /*<<< orphan*/ ,char*) ; 
 int MG_MQTT_CMD_PUBLISH ; 
 int /*<<< orphan*/  mbuf_append (struct mbuf*,char*,int) ; 
 int /*<<< orphan*/  mbuf_free (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_init (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mg_mqtt_message*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_mqtt (struct mbuf*,struct mg_mqtt_message*) ; 

__attribute__((used)) static const char *test_mqtt_parse_mqtt_qos1(void) {
  /* clang-format off */
  struct mg_mqtt_message mm;
  char msg_qos1[] = {
      ((MG_MQTT_CMD_PUBLISH << 4) | (1 << 1)),
      2 + 6 + 2 + 7,
      0, 6, '/', 't', 'o', 'p', 'i', 'c',
      0x12, 0x34,
      'p', 'a', 'y', 'l', 'o', 'a', 'd',
  };
  /* clang-format on */
  struct mbuf mb;
  memset(&mm, 0, sizeof(mm));
  mbuf_init(&mb, 0);
  mbuf_append(&mb, msg_qos1, sizeof(msg_qos1));
  ASSERT_EQ(parse_mqtt(&mb, &mm), (int) sizeof(msg_qos1));
  ASSERT_EQ(mm.cmd, MG_MQTT_CMD_PUBLISH);
  ASSERT_EQ(mm.qos, 1);
  ASSERT_EQ(mm.message_id, 0x1234);
  ASSERT_EQ(mm.topic.len, 6);
  ASSERT_STREQ_NZ(mm.topic.p, "/topic");
  ASSERT_EQ(mm.payload.len, 7);
  ASSERT_STREQ_NZ(mm.payload.p, "payload");
  mbuf_free(&mb);
  return NULL;
}