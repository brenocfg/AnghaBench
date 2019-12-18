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
struct work_result {int member_1; int /*<<< orphan*/  member_0; } ;
struct work_request {int /*<<< orphan*/  conn_id; int /*<<< orphan*/  member_0; } ;
struct mg_mgr {int dummy; } ;
typedef  int /*<<< orphan*/  res ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  mg_broadcast (struct mg_mgr*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  on_work_complete ; 
 int /*<<< orphan*/  perror (char*) ; 
 int rand () ; 
 scalar_t__ read (int /*<<< orphan*/ ,struct work_request*,int) ; 
 scalar_t__ s_received_signal ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/ * sock ; 

void *worker_thread_proc(void *param) {
  struct mg_mgr *mgr = (struct mg_mgr *) param;
  struct work_request req = {0};
  
  while (s_received_signal == 0) {
    if (read(sock[1], &req, sizeof(req)) < 0)
      perror("Reading worker sock");
    int r = rand() % 10;
    sleep(r);
    struct work_result res = {req.conn_id, r};
    mg_broadcast(mgr, on_work_complete, (void *)&res, sizeof(res));
  }
  return NULL;
}