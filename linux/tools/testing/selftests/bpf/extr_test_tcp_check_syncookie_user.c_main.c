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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in6 {scalar_t__ sin6_port; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; scalar_t__ sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr_in {scalar_t__ sin6_port; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; scalar_t__ sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addr6 ;
typedef  int /*<<< orphan*/  addr4 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int get_map_fd_by_prog_id (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6addr_loopback ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ run_test (int,int,int) ; 
 int start_server (struct sockaddr const*,int) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv)
{
	struct sockaddr_in addr4;
	struct sockaddr_in6 addr6;
	int server = -1;
	int server_v6 = -1;
	int results = -1;
	int err = 0;
	bool xdp;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s prog_id\n", argv[0]);
		exit(1);
	}

	results = get_map_fd_by_prog_id(atoi(argv[1]), &xdp);
	if (results < 0) {
		log_err("Can't get map");
		goto err;
	}

	memset(&addr4, 0, sizeof(addr4));
	addr4.sin_family = AF_INET;
	addr4.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	addr4.sin_port = 0;

	memset(&addr6, 0, sizeof(addr6));
	addr6.sin6_family = AF_INET6;
	addr6.sin6_addr = in6addr_loopback;
	addr6.sin6_port = 0;

	server = start_server((const struct sockaddr *)&addr4, sizeof(addr4));
	if (server == -1)
		goto err;

	server_v6 = start_server((const struct sockaddr *)&addr6,
				 sizeof(addr6));
	if (server_v6 == -1)
		goto err;

	if (run_test(server, results, xdp))
		goto err;

	if (run_test(server_v6, results, xdp))
		goto err;

	printf("ok\n");
	goto out;
err:
	err = 1;
out:
	close(server);
	close(server_v6);
	close(results);
	return err;
}