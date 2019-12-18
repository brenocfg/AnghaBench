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
struct mg_mgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  ev_handler ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * mg_connect (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 char* s_address ; 
 char* s_password ; 
 char* s_topic ; 
 char* s_user_name ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 

int main(int argc, char **argv) {
  struct mg_mgr mgr;
  int i;

  mg_mgr_init(&mgr, NULL);

  /* Parse command line arguments */
  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0) {
      s_address = argv[++i];
    } else if (strcmp(argv[i], "-u") == 0) {
      s_user_name = argv[++i];
    } else if (strcmp(argv[i], "-t") == 0) {
      s_topic = argv[++i];
    } else if (strcmp(argv[i], "-p") == 0) {
      s_password = argv[++i];
    }
  }

  if (mg_connect(&mgr, s_address, ev_handler) == NULL) {
    fprintf(stderr, "mg_connect(%s) failed\n", s_address);
    exit(EXIT_FAILURE);
  }

  for (;;) {
    mg_mgr_poll(&mgr, 1000);
  }
}