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
struct mg_dns_message {int /*<<< orphan*/  num_answers; int /*<<< orphan*/  num_questions; int /*<<< orphan*/  flags; int /*<<< orphan*/  transaction_id; } ;
struct mg_dns_header {void* num_answers; void* num_questions; void* flags; int /*<<< orphan*/  transaction_id; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  header ;

/* Variables and functions */
 void* htons (int /*<<< orphan*/ ) ; 
 int mbuf_insert (struct mbuf*,size_t,struct mg_dns_header*,int) ; 
 int /*<<< orphan*/  memset (struct mg_dns_header*,int /*<<< orphan*/ ,int) ; 

int mg_dns_insert_header(struct mbuf *io, size_t pos,
                         struct mg_dns_message *msg) {
  struct mg_dns_header header;

  memset(&header, 0, sizeof(header));
  header.transaction_id = msg->transaction_id;
  header.flags = htons(msg->flags);
  header.num_questions = htons(msg->num_questions);
  header.num_answers = htons(msg->num_answers);

  return mbuf_insert(io, pos, &header, sizeof(header));
}