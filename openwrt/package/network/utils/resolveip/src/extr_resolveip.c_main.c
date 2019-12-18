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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sigaction {int /*<<< orphan*/ * sa_handler; } ;
struct addrinfo {scalar_t__ ai_family; scalar_t__ ai_addr; struct addrinfo* ai_next; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNSPEC ; 
 int INET6_ADDRSTRLEN ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  abort_query ; 
 int /*<<< orphan*/  alarm (int) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 scalar_t__ getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  inet_ntop (scalar_t__,void*,char*,int) ; 
 int /*<<< orphan*/  optarg ; 
 size_t optind ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  show_usage () ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
	int timeout = 3;
	int opt;
	char ipaddr[INET6_ADDRSTRLEN];
	void *addr;
	struct addrinfo *res, *rp;
	struct sigaction sa = {	.sa_handler = &abort_query };
	struct addrinfo hints = {
		.ai_family   = AF_UNSPEC,
		.ai_socktype = SOCK_STREAM,
		.ai_protocol = IPPROTO_TCP,
		.ai_flags    = 0
	};

	while ((opt = getopt(argc, argv, "46t:h")) > -1)
	{
		switch ((char)opt)
		{
			case '4':
				hints.ai_family = AF_INET;
				break;

			case '6':
				hints.ai_family = AF_INET6;
				break;

			case 't':
				timeout = atoi(optarg);
				if (timeout <= 0)
					show_usage();
				break;

			case 'h':
				show_usage();
				break;
		}
	}

	if (!argv[optind])
		show_usage();

	sigaction(SIGALRM, &sa, NULL);
	alarm(timeout);

	if (getaddrinfo(argv[optind], NULL, &hints, &res))
		exit(2);

	for (rp = res; rp != NULL; rp = rp->ai_next)
	{
		addr = (rp->ai_family == AF_INET)
			? (void *)&((struct sockaddr_in *)rp->ai_addr)->sin_addr
			: (void *)&((struct sockaddr_in6 *)rp->ai_addr)->sin6_addr
		;

		if (!inet_ntop(rp->ai_family, addr, ipaddr, INET6_ADDRSTRLEN - 1))
			exit(3);

		printf("%s\n", ipaddr);
	}

	freeaddrinfo(res);
	exit(0);
}