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
struct simple_data {int /*<<< orphan*/  data_rcvd; int /*<<< orphan*/  fail; int /*<<< orphan*/  to_send; } ;
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct mg_connection {TYPE_1__ recv_mbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  mbuf_remove (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void do_recv(struct simple_data *d, struct mg_connection *nc,
                    void *ev_data) {
  if (*((int *) ev_data) != (int) nc->recv_mbuf.len) {
    char msg[100];
    sprintf(msg, "(num recv wrong: %d vs %d)", *((int *) ev_data),
            (int) strlen(d->to_send));
    strcat(d->fail, msg);
    return;
  }
  strncat(d->data_rcvd, nc->recv_mbuf.buf, nc->recv_mbuf.len);
  mbuf_remove(&nc->recv_mbuf, nc->recv_mbuf.len);
}