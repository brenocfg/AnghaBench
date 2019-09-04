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
struct simple_data {char* to_send; int /*<<< orphan*/  fail; } ;
struct TYPE_2__ {scalar_t__ len; } ;
struct mg_connection {TYPE_1__ send_mbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void check_sent(struct simple_data *d, struct mg_connection *nc,
                       void *ev_data) {
  if (*((int *) ev_data) != (int) strlen(d->to_send)) {
    char msg[100];
    sprintf(msg, "(num sent wrong: %d vs %d)", *((int *) ev_data),
            (int) strlen(d->to_send));
    strcat(d->fail, msg);
  } else {
    d->to_send[0] = '\0';
  }
  if (nc->send_mbuf.len != 0) strcat(d->fail, "(send buf not empty)");
}