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
typedef  int /*<<< orphan*/  uint16_t ;
struct mg_dns_resource_record {int rtype; int rclass; int /*<<< orphan*/  kind; } ;
struct mg_dns_message {int flags; int num_questions; scalar_t__ transaction_id; struct mg_dns_resource_record* questions; } ;
struct mg_connection {int flags; } ;
struct mbuf {scalar_t__ len; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 scalar_t__ MG_CALLOC (int,int) ; 
 int /*<<< orphan*/  MG_DNS_QUESTION ; 
 int /*<<< orphan*/  MG_FREE (struct mg_dns_message*) ; 
 int MG_F_UDP ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_free (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_init (struct mbuf*,int) ; 
 int /*<<< orphan*/  mbuf_insert (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int mg_dns_encode_record (struct mbuf*,struct mg_dns_resource_record*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_dns_insert_header (struct mbuf*,int /*<<< orphan*/ ,struct mg_dns_message*) ; 
 scalar_t__ mg_dns_tid ; 
 int /*<<< orphan*/  mg_send (struct mg_connection*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void mg_send_dns_query(struct mg_connection *nc, const char *name,
                       int query_type) {
  struct mg_dns_message *msg =
      (struct mg_dns_message *) MG_CALLOC(1, sizeof(*msg));
  struct mbuf pkt;
  struct mg_dns_resource_record *rr = &msg->questions[0];

  DBG(("%s %d", name, query_type));

  mbuf_init(&pkt, 64 /* Start small, it'll grow as needed. */);

  msg->transaction_id = ++mg_dns_tid;
  msg->flags = 0x100;
  msg->num_questions = 1;

  mg_dns_insert_header(&pkt, 0, msg);

  rr->rtype = query_type;
  rr->rclass = 1; /* Class: inet */
  rr->kind = MG_DNS_QUESTION;

  if (mg_dns_encode_record(&pkt, rr, name, strlen(name), NULL, 0) == -1) {
    /* TODO(mkm): return an error code */
    goto cleanup; /* LCOV_EXCL_LINE */
  }

  /* TCP DNS requires messages to be prefixed with len */
  if (!(nc->flags & MG_F_UDP)) {
    uint16_t len = htons((uint16_t) pkt.len);
    mbuf_insert(&pkt, 0, &len, 2);
  }

  mg_send(nc, pkt.buf, pkt.len);
  mbuf_free(&pkt);

cleanup:
  MG_FREE(msg);
}