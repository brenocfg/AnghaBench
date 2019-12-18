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
typedef  int /*<<< orphan*/  val ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ control_fd ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char const*,char const*,struct addrinfo*,struct addrinfo**) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

void control_init(const char *control_host,
		  const char *control_port,
		  bool server)
{
	struct addrinfo hints = {
		.ai_socktype = SOCK_STREAM,
	};
	struct addrinfo *result = NULL;
	struct addrinfo *ai;
	int ret;

	ret = getaddrinfo(control_host, control_port, &hints, &result);
	if (ret != 0) {
		fprintf(stderr, "%s\n", gai_strerror(ret));
		exit(EXIT_FAILURE);
	}

	for (ai = result; ai; ai = ai->ai_next) {
		int fd;
		int val = 1;

		fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
		if (fd < 0)
			continue;

		if (!server) {
			if (connect(fd, ai->ai_addr, ai->ai_addrlen) < 0)
				goto next;
			control_fd = fd;
			printf("Control socket connected to %s:%s.\n",
			       control_host, control_port);
			break;
		}

		if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,
			       &val, sizeof(val)) < 0) {
			perror("setsockopt");
			exit(EXIT_FAILURE);
		}

		if (bind(fd, ai->ai_addr, ai->ai_addrlen) < 0)
			goto next;
		if (listen(fd, 1) < 0)
			goto next;

		printf("Control socket listening on %s:%s\n",
		       control_host, control_port);
		fflush(stdout);

		control_fd = accept(fd, NULL, 0);
		close(fd);

		if (control_fd < 0) {
			perror("accept");
			exit(EXIT_FAILURE);
		}
		printf("Control socket connection accepted...\n");
		break;

next:
		close(fd);
	}

	if (control_fd < 0) {
		fprintf(stderr, "Control socket initialization failed.  Invalid address %s:%s?\n",
			control_host, control_port);
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(result);
}