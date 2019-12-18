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
struct TYPE_3__ {int len; scalar_t__ p; } ;
struct mg_dns_resource_record {TYPE_1__ name; } ;
struct TYPE_4__ {scalar_t__ p; } ;
struct mg_dns_message {int num_questions; struct mg_dns_resource_record* questions; TYPE_2__ pkt; } ;
struct mg_dns_header {int dummy; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int mbuf_append (struct mbuf*,unsigned char*,int) ; 

int mg_dns_copy_questions(struct mbuf *io, struct mg_dns_message *msg) {
  unsigned char *begin, *end;
  struct mg_dns_resource_record *last_q;
  if (msg->num_questions <= 0) return 0;
  begin = (unsigned char *) msg->pkt.p + sizeof(struct mg_dns_header);
  last_q = &msg->questions[msg->num_questions - 1];
  end = (unsigned char *) last_q->name.p + last_q->name.len + 4;
  return mbuf_append(io, begin, end - begin);
}