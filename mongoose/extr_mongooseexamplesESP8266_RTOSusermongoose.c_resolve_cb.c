#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mg_dns_message {int num_answers; TYPE_3__* answers; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_5__ {TYPE_1__ sin; } ;
struct mg_connection {int flags; int /*<<< orphan*/  user_data; TYPE_2__ sa; } ;
typedef  enum mg_resolve_err { ____Placeholder_mg_resolve_err } mg_resolve_err ;
struct TYPE_6__ {scalar_t__ rtype; } ;

/* Variables and functions */
 scalar_t__ MG_DNS_A_RECORD ; 
 int /*<<< orphan*/  MG_EV_CLOSE ; 
 int /*<<< orphan*/  MG_EV_CONNECT ; 
 int /*<<< orphan*/  MG_EV_TIMER ; 
 int MG_F_RESOLVING ; 
 int MG_F_UDP ; 
 int MG_RESOLVE_TIMEOUT ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  mg_call (struct mg_connection*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mg_destroy_conn (struct mg_connection*,int) ; 
 int /*<<< orphan*/  mg_dns_parse_record_data (struct mg_dns_message*,TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mg_do_connect (struct mg_connection*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 double mg_time () ; 

__attribute__((used)) static void resolve_cb(struct mg_dns_message *msg, void *data,
                       enum mg_resolve_err e) {
  struct mg_connection *nc = (struct mg_connection *) data;
  int i;
  int failure = -1;

  nc->flags &= ~MG_F_RESOLVING;
  if (msg != NULL) {
    /*
     * Take the first DNS A answer and run...
     */
    for (i = 0; i < msg->num_answers; i++) {
      if (msg->answers[i].rtype == MG_DNS_A_RECORD) {
        /*
         * Async resolver guarantees that there is at least one answer.
         * TODO(lsm): handle IPv6 answers too
         */
        mg_dns_parse_record_data(msg, &msg->answers[i], &nc->sa.sin.sin_addr,
                                 4);
        mg_do_connect(nc, nc->flags & MG_F_UDP ? SOCK_DGRAM : SOCK_STREAM,
                      &nc->sa);
        return;
      }
    }
  }

  if (e == MG_RESOLVE_TIMEOUT) {
    double now = mg_time();
    mg_call(nc, NULL, nc->user_data, MG_EV_TIMER, &now);
  }

  /*
   * If we get there was no MG_DNS_A_RECORD in the answer
   */
  mg_call(nc, NULL, nc->user_data, MG_EV_CONNECT, &failure);
  mg_call(nc, NULL, nc->user_data, MG_EV_CLOSE, NULL);
  mg_destroy_conn(nc, 1 /* destroy_if */);
}