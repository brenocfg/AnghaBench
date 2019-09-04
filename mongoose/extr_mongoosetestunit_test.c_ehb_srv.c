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
struct mbuf {int dummy; } ;
struct mg_connection {TYPE_1__* mgr; struct mbuf recv_mbuf; } ;
struct TYPE_2__ {scalar_t__ user_data; } ;

/* Variables and functions */
 int MG_EV_RECV ; 
 int /*<<< orphan*/  mbuf_remove (struct mbuf*,int) ; 

__attribute__((used)) static void ehb_srv(struct mg_connection *nc, int ev, void *p) {
  struct mbuf *io = &nc->recv_mbuf;
  (void) io;
  (void) p;

  if (ev == MG_EV_RECV) {
    if (*(int *) p == 1) (*(int *) nc->mgr->user_data)++;
    mbuf_remove(io, *(int *) p);
  }
}