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
struct vsock_diag_msg {int dummy; } ;
struct nlmsghdr {int nlmsg_type; scalar_t__ nlmsg_len; } ;
struct nlmsgerr {int /*<<< orphan*/  error; } ;
struct list_head {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NETLINK ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  NETLINK_SOCK_DIAG ; 
 struct nlmsgerr* NLMSG_DATA (struct nlmsghdr const*) ; 
 int NLMSG_DONE ; 
 int NLMSG_ERROR ; 
 scalar_t__ NLMSG_LENGTH (int) ; 
 struct nlmsghdr* NLMSG_NEXT (struct nlmsghdr const*,int) ; 
 scalar_t__ NLMSG_OK (struct nlmsghdr const*,int) ; 
 int SOCK_DIAG_BY_FAMILY ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  add_vsock_stat (struct list_head*,struct nlmsgerr*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int recv_resp (int,long*,int) ; 
 int /*<<< orphan*/  send_req (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void read_vsock_stat(struct list_head *sockets)
{
	long buf[8192 / sizeof(long)];
	int fd;

	fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_SOCK_DIAG);
	if (fd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	send_req(fd);

	for (;;) {
		const struct nlmsghdr *h;
		ssize_t ret;

		ret = recv_resp(fd, buf, sizeof(buf));
		if (ret == 0)
			goto done;
		if (ret < sizeof(*h)) {
			fprintf(stderr, "short read of %zd bytes\n", ret);
			exit(EXIT_FAILURE);
		}

		h = (struct nlmsghdr *)buf;

		while (NLMSG_OK(h, ret)) {
			if (h->nlmsg_type == NLMSG_DONE)
				goto done;

			if (h->nlmsg_type == NLMSG_ERROR) {
				const struct nlmsgerr *err = NLMSG_DATA(h);

				if (h->nlmsg_len < NLMSG_LENGTH(sizeof(*err)))
					fprintf(stderr, "NLMSG_ERROR\n");
				else {
					errno = -err->error;
					perror("NLMSG_ERROR");
				}

				exit(EXIT_FAILURE);
			}

			if (h->nlmsg_type != SOCK_DIAG_BY_FAMILY) {
				fprintf(stderr, "unexpected nlmsg_type %#x\n",
					h->nlmsg_type);
				exit(EXIT_FAILURE);
			}
			if (h->nlmsg_len <
			    NLMSG_LENGTH(sizeof(struct vsock_diag_msg))) {
				fprintf(stderr, "short vsock_diag_msg\n");
				exit(EXIT_FAILURE);
			}

			add_vsock_stat(sockets, NLMSG_DATA(h));

			h = NLMSG_NEXT(h, ret);
		}
	}

done:
	close(fd);
}