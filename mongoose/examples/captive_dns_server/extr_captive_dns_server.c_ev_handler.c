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
struct mg_dns_resource_record {int rtype; int /*<<< orphan*/  name; } ;
struct mg_dns_reply {int dummy; } ;
struct mg_dns_message {int num_questions; struct mg_dns_resource_record* questions; } ;
struct mg_connection {int /*<<< orphan*/  flags; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  rname ;

/* Variables and functions */
 int MG_DNS_A_RECORD ; 
#define  MG_DNS_MESSAGE 128 
 int /*<<< orphan*/  MG_F_SEND_AND_CLOSE ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  mbuf_free (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_init (struct mbuf*,int) ; 
 struct mg_dns_reply mg_dns_create_reply (struct mbuf*,struct mg_dns_message*) ; 
 int /*<<< orphan*/  mg_dns_reply_record (struct mg_dns_reply*,struct mg_dns_resource_record*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mg_dns_send_reply (struct mg_connection*,struct mg_dns_reply*) ; 
 int /*<<< orphan*/  mg_dns_uncompress_name (struct mg_dns_message*,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  s_our_ip_addr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  struct mg_dns_message *msg;
  struct mg_dns_resource_record *rr;
  struct mg_dns_reply reply;
  int i;

  switch (ev) {
    case MG_DNS_MESSAGE: {
      struct mbuf reply_buf;
      mbuf_init(&reply_buf, 512);
      msg = (struct mg_dns_message *) ev_data;
      reply = mg_dns_create_reply(&reply_buf, msg);

      for (i = 0; i < msg->num_questions; i++) {
        char rname[256];
        rr = &msg->questions[i];
        mg_dns_uncompress_name(msg, &rr->name, rname, sizeof(rname) - 1);
        fprintf(stdout, "Q type %d name %s\n", rr->rtype, rname);
        if (rr->rtype == MG_DNS_A_RECORD) {
          mg_dns_reply_record(&reply, rr, NULL, rr->rtype, 10, &s_our_ip_addr,
                              4);
        }
      }

      /*
       * We don't set the error flag even if there were no answers
       * matching the MG_DNS_A_RECORD query type.
       * This indicates that we have (synthetic) answers for MG_DNS_A_RECORD.
       * See http://goo.gl/QWvufr for a distinction between NXDOMAIN and NODATA.
       */

      mg_dns_send_reply(nc, &reply);
      nc->flags |= MG_F_SEND_AND_CLOSE;
      mbuf_free(&reply_buf);
      break;
    }
  }
}