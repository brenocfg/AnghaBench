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
struct TYPE_2__ {char const* p; int len; } ;
struct mg_dns_message {int num_questions; int num_answers; int /*<<< orphan*/ * answers; int /*<<< orphan*/ * questions; void* flags; int /*<<< orphan*/  transaction_id; TYPE_1__ pkt; } ;
struct mg_dns_header {int /*<<< orphan*/  num_answers; int /*<<< orphan*/  num_questions; int /*<<< orphan*/  flags; int /*<<< orphan*/  transaction_id; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct mg_dns_message*,int /*<<< orphan*/ ,int) ; 
 unsigned char* mg_parse_dns_resource_record (unsigned char*,unsigned char*,int /*<<< orphan*/ *,int) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 

int mg_parse_dns(const char *buf, int len, struct mg_dns_message *msg) {
  struct mg_dns_header *header = (struct mg_dns_header *) buf;
  unsigned char *data = (unsigned char *) buf + sizeof(*header);
  unsigned char *end = (unsigned char *) buf + len;
  int i;

  memset(msg, 0, sizeof(*msg));
  msg->pkt.p = buf;
  msg->pkt.len = len;

  if (len < (int) sizeof(*header)) return -1;

  msg->transaction_id = header->transaction_id;
  msg->flags = ntohs(header->flags);
  msg->num_questions = ntohs(header->num_questions);
  if (msg->num_questions > (int) ARRAY_SIZE(msg->questions)) {
    msg->num_questions = (int) ARRAY_SIZE(msg->questions);
  }
  msg->num_answers = ntohs(header->num_answers);
  if (msg->num_answers > (int) ARRAY_SIZE(msg->answers)) {
    msg->num_answers = (int) ARRAY_SIZE(msg->answers);
  }

  for (i = 0; i < msg->num_questions; i++) {
    data = mg_parse_dns_resource_record(data, end, &msg->questions[i], 0);
    if (data == NULL) return -1;
  }

  for (i = 0; i < msg->num_answers; i++) {
    data = mg_parse_dns_resource_record(data, end, &msg->answers[i], 1);
    if (data == NULL) return -1;
  }

  return 0;
}