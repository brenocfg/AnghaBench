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
struct sockaddr_in {void* sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  one ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  S1_PORT ; 
 int /*<<< orphan*/  S2_PORT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bind (int,struct sockaddr*,int) ; 
 int c1 ; 
 int c2 ; 
 int connect (int,struct sockaddr*,int) ; 
 int errno ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,char*) ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ p1 ; 
 scalar_t__ p2 ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int s1 ; 
 int s2 ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sockmap_init_sockets(int verbose)
{
	int i, err, one = 1;
	struct sockaddr_in addr;
	int *fds[4] = {&s1, &s2, &c1, &c2};

	s1 = s2 = p1 = p2 = c1 = c2 = 0;

	/* Init sockets */
	for (i = 0; i < 4; i++) {
		*fds[i] = socket(AF_INET, SOCK_STREAM, 0);
		if (*fds[i] < 0) {
			perror("socket s1 failed()");
			return errno;
		}
	}

	/* Allow reuse */
	for (i = 0; i < 2; i++) {
		err = setsockopt(*fds[i], SOL_SOCKET, SO_REUSEADDR,
				 (char *)&one, sizeof(one));
		if (err) {
			perror("setsockopt failed()");
			return errno;
		}
	}

	/* Non-blocking sockets */
	for (i = 0; i < 2; i++) {
		err = ioctl(*fds[i], FIONBIO, (char *)&one);
		if (err < 0) {
			perror("ioctl s1 failed()");
			return errno;
		}
	}

	/* Bind server sockets */
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	addr.sin_port = htons(S1_PORT);
	err = bind(s1, (struct sockaddr *)&addr, sizeof(addr));
	if (err < 0) {
		perror("bind s1 failed()\n");
		return errno;
	}

	addr.sin_port = htons(S2_PORT);
	err = bind(s2, (struct sockaddr *)&addr, sizeof(addr));
	if (err < 0) {
		perror("bind s2 failed()\n");
		return errno;
	}

	/* Listen server sockets */
	addr.sin_port = htons(S1_PORT);
	err = listen(s1, 32);
	if (err < 0) {
		perror("listen s1 failed()\n");
		return errno;
	}

	addr.sin_port = htons(S2_PORT);
	err = listen(s2, 32);
	if (err < 0) {
		perror("listen s1 failed()\n");
		return errno;
	}

	/* Initiate Connect */
	addr.sin_port = htons(S1_PORT);
	err = connect(c1, (struct sockaddr *)&addr, sizeof(addr));
	if (err < 0 && errno != EINPROGRESS) {
		perror("connect c1 failed()\n");
		return errno;
	}

	addr.sin_port = htons(S2_PORT);
	err = connect(c2, (struct sockaddr *)&addr, sizeof(addr));
	if (err < 0 && errno != EINPROGRESS) {
		perror("connect c2 failed()\n");
		return errno;
	} else if (err < 0) {
		err = 0;
	}

	/* Accept Connecrtions */
	p1 = accept(s1, NULL, NULL);
	if (p1 < 0) {
		perror("accept s1 failed()\n");
		return errno;
	}

	p2 = accept(s2, NULL, NULL);
	if (p2 < 0) {
		perror("accept s1 failed()\n");
		return errno;
	}

	if (verbose) {
		printf("connected sockets: c1 <-> p1, c2 <-> p2\n");
		printf("cgroups binding: c1(%i) <-> s1(%i) - - - c2(%i) <-> s2(%i)\n",
			c1, s1, c2, s2);
	}
	return 0;
}