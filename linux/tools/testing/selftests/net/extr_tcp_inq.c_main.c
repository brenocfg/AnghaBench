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
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct msghdr {int msg_iovlen; char* msg_control; int msg_controllen; int msg_flags; struct iovec* msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct iovec {char* iov_base; int iov_len; } ;
struct cmsghdr {scalar_t__ cmsg_level; scalar_t__ cmsg_type; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  one ;
typedef  int /*<<< orphan*/  cmsgbuf ;

/* Variables and functions */
 int BUF_SIZE ; 
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 int CMSG_SIZE ; 
 int MSG_CTRUNC ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ SOL_SOCKET ; 
 scalar_t__ SOL_TCP ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ TCP_CM_INQ ; 
 int /*<<< orphan*/  TCP_INQ ; 
 int addr_len ; 
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 int bind (int,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  family ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 int listen (int,int) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int recvmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int,scalar_t__,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  setup_loopback_addr (int /*<<< orphan*/ ,struct sockaddr_storage*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_server ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char *argv[])
{
	struct sockaddr_storage listen_addr, addr;
	int c, one = 1, inq = -1;
	pthread_t server_thread;
	char cmsgbuf[CMSG_SIZE];
	struct iovec iov[1];
	struct cmsghdr *cm;
	struct msghdr msg;
	int server_fd, fd;
	char *buf;

	while ((c = getopt(argc, argv, "46p:")) != -1) {
		switch (c) {
		case '4':
			family = PF_INET;
			addr_len = sizeof(struct sockaddr_in);
			break;
		case '6':
			family = PF_INET6;
			addr_len = sizeof(struct sockaddr_in6);
			break;
		case 'p':
			port = atoi(optarg);
			break;
		}
	}

	server_fd = socket(family, SOCK_STREAM, 0);
	if (server_fd < 0)
		error(1, errno, "server socket");
	setup_loopback_addr(family, &listen_addr);
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
		       &one, sizeof(one)) != 0)
		error(1, errno, "setsockopt(SO_REUSEADDR)");
	if (bind(server_fd, (const struct sockaddr *)&listen_addr,
		 addr_len) == -1)
		error(1, errno, "bind");
	if (listen(server_fd, 128) == -1)
		error(1, errno, "listen");
	if (pthread_create(&server_thread, NULL, start_server,
			   (void *)(unsigned long)server_fd) != 0)
		error(1, errno, "pthread_create");

	fd = socket(family, SOCK_STREAM, 0);
	if (fd < 0)
		error(1, errno, "client socket");
	setup_loopback_addr(family, &addr);
	if (connect(fd, (const struct sockaddr *)&addr, addr_len) == -1)
		error(1, errno, "connect");
	if (setsockopt(fd, SOL_TCP, TCP_INQ, &one, sizeof(one)) != 0)
		error(1, errno, "setsockopt(TCP_INQ)");

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;
	msg.msg_control = cmsgbuf;
	msg.msg_controllen = sizeof(cmsgbuf);
	msg.msg_flags = 0;

	buf = malloc(BUF_SIZE);
	iov[0].iov_base = buf;
	iov[0].iov_len = BUF_SIZE / 2;

	if (recvmsg(fd, &msg, 0) != iov[0].iov_len)
		error(1, errno, "recvmsg");
	if (msg.msg_flags & MSG_CTRUNC)
		error(1, 0, "control message is truncated");

	for (cm = CMSG_FIRSTHDR(&msg); cm; cm = CMSG_NXTHDR(&msg, cm))
		if (cm->cmsg_level == SOL_TCP && cm->cmsg_type == TCP_CM_INQ)
			inq = *((int *) CMSG_DATA(cm));

	if (inq != BUF_SIZE - iov[0].iov_len) {
		fprintf(stderr, "unexpected inq: %d\n", inq);
		exit(1);
	}

	printf("PASSED\n");
	free(buf);
	close(fd);
	return 0;
}