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
struct work_request {unsigned long member_0; } ;
struct mg_connection {int /*<<< orphan*/ * user_data; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
#define  MG_EV_ACCEPT 130 
#define  MG_EV_CLOSE 129 
#define  MG_EV_HTTP_REQUEST 128 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ s_next_id ; 
 int /*<<< orphan*/ * sock ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,struct work_request*,int) ; 

__attribute__((used)) static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  (void) nc;
  (void) ev_data;
  
  switch (ev) {
    case MG_EV_ACCEPT:
      nc->user_data = (void *)++s_next_id;
      break;
    case MG_EV_HTTP_REQUEST: {
      struct work_request req = {(unsigned long)nc->user_data};

      if (write(sock[0], &req, sizeof(req)) < 0)
        perror("Writing worker sock");
      break;
    }
    case MG_EV_CLOSE: {
      if (nc->user_data) nc->user_data = NULL;
    }
  }
}