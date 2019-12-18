#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mg_mgr {int dummy; } ;
struct mg_connection {int /*<<< orphan*/  sock; } ;
struct TYPE_4__ {void* s_addr; } ;
struct TYPE_3__ {void* s_addr; } ;
struct ip_mreq {TYPE_2__ imr_interface; TYPE_1__ imr_multiaddr; } ;
typedef  int /*<<< orphan*/  listen ;
typedef  int /*<<< orphan*/  group ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_ADD_MEMBERSHIP ; 
 char* MCAST_GROUP ; 
 int /*<<< orphan*/  ev_handler ; 
 int /*<<< orphan*/  exit (int) ; 
 void* inet_addr (char const*) ; 
 struct mg_connection* mg_bind (struct mg_mgr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_mgr_free (struct mg_mgr*) ; 
 int /*<<< orphan*/  mg_mgr_init (struct mg_mgr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mg_mgr_poll (struct mg_mgr*,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage (char**) ; 

int main(int argc, char **argv) {
  struct mg_mgr mgr;
  const char *port = "1234";
  struct mg_connection *nc;
  struct ip_mreq group;
  const char *interface = NULL;
  const char *mcast_group = MCAST_GROUP;
  int i;

  /* Parse command line arguments */
  for (i = 1; i < argc; i++) {
    // IP address of the interface where to join a multicast group.
    if (strcmp(argv[i], "-i") == 0) {
      interface = argv[++i];
    } else if (strcmp(argv[i], "-g") == 0) {
      mcast_group = argv[++i];
    } else if (strcmp(argv[i], "-p") == 0) {
      port = argv[++i];
    }
  }

  if (interface == NULL) {
    usage(argv);
  }

  mg_mgr_init(&mgr, NULL);
  {
    char listen[256];
    snprintf(listen, sizeof(listen), "udp://%s", port);
    nc = mg_bind(&mgr, listen, ev_handler);
  }

  if (nc == NULL) {
    perror("cannot bind\n");
    exit(1);
  }

  group.imr_multiaddr.s_addr = inet_addr(mcast_group);
  group.imr_interface.s_addr = inet_addr(interface);
  if (setsockopt(nc->sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *) &group,
                 sizeof(group)) < 0) {
    perror("Adding multicast group error");
    exit(1);
  }

  printf("Starting mcast server on port %s listening to group %s\n", port,
         mcast_group);
  for (;;) {
    mg_mgr_poll(&mgr, 1000);
  }
  mg_mgr_free(&mgr);

  return 0;
}