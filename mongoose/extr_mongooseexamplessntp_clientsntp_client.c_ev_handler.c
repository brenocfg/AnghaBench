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
typedef  int /*<<< orphan*/  time_t ;
struct mg_sntp_message {int /*<<< orphan*/  time; } ;
struct mg_connection {int dummy; } ;

/* Variables and functions */
#define  MG_SNTP_FAILED 129 
#define  MG_SNTP_REPLY 128 
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* s_default_server ; 
 int s_exit_flag ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ev_handler(struct mg_connection *c, int ev, void *ev_data) {
  struct mg_sntp_message *sm = (struct mg_sntp_message *) ev_data;
  time_t t;
  (void) c;

  switch (ev) {
    case MG_SNTP_REPLY:
      t = time(NULL);
      fprintf(stdout, "Local time: %s", ctime(&t));
      t = (time_t) sm->time;
      fprintf(stdout, "Time from %s: %s", s_default_server, ctime(&t));
      s_exit_flag = 1;
      break;
    case MG_SNTP_FAILED:
      fprintf(stderr, "Failed to get time\n");
      s_exit_flag = 1;
      break;
  }
}