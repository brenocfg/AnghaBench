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
typedef  int /*<<< orphan*/  time_t ;
struct sockaddr_nl {int nl_groups; scalar_t__ nl_pid; int /*<<< orphan*/  nl_family; } ;
struct sockaddr {int dummy; } ;
struct pollfd {int fd; scalar_t__ revents; int /*<<< orphan*/  events; } ;
struct nlmsghdr {int nlmsg_type; } ;
struct TYPE_2__ {int idx; int val; } ;
struct cn_msg {int seq; int ack; TYPE_1__ id; scalar_t__ len; } ;
typedef  int /*<<< orphan*/  on ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NETLINK ; 
 int CN_TEST_IDX ; 
 int CN_TEST_VAL ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  NETLINK_ADD_MEMBERSHIP ; 
 int /*<<< orphan*/  NETLINK_CONNECTOR ; 
 scalar_t__ NLMSG_DATA (struct nlmsghdr*) ; 
#define  NLMSG_DONE 129 
#define  NLMSG_ERROR 128 
 int /*<<< orphan*/  PF_NETLINK ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_NETLINK ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int need_exit ; 
 int netlink_send (int,struct cn_msg*) ; 
 int optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int poll (struct pollfd*,int,int) ; 
 int recv (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ulog (char*,...) ; 
 int /*<<< orphan*/  usage () ; 

int main(int argc, char *argv[])
{
	int s;
	char buf[1024];
	int len;
	struct nlmsghdr *reply;
	struct sockaddr_nl l_local;
	struct cn_msg *data;
	FILE *out;
	time_t tm;
	struct pollfd pfd;
	bool send_msgs = false;

	while ((s = getopt(argc, argv, "hs")) != -1) {
		switch (s) {
		case 's':
			send_msgs = true;
			break;

		case 'h':
			usage();
			return 0;

		default:
			/* getopt() outputs an error for us */
			usage();
			return 1;
		}
	}

	if (argc != optind) {
		out = fopen(argv[optind], "a+");
		if (!out) {
			ulog("Unable to open %s for writing: %s\n",
				argv[1], strerror(errno));
			out = stdout;
		}
	} else
		out = stdout;

	memset(buf, 0, sizeof(buf));

	s = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_CONNECTOR);
	if (s == -1) {
		perror("socket");
		return -1;
	}

	l_local.nl_family = AF_NETLINK;
	l_local.nl_groups = -1; /* bitmask of requested groups */
	l_local.nl_pid = 0;

	ulog("subscribing to %u.%u\n", CN_TEST_IDX, CN_TEST_VAL);

	if (bind(s, (struct sockaddr *)&l_local, sizeof(struct sockaddr_nl)) == -1) {
		perror("bind");
		close(s);
		return -1;
	}

#if 0
	{
		int on = 0x57; /* Additional group number */
		setsockopt(s, SOL_NETLINK, NETLINK_ADD_MEMBERSHIP, &on, sizeof(on));
	}
#endif
	if (send_msgs) {
		int i, j;

		memset(buf, 0, sizeof(buf));

		data = (struct cn_msg *)buf;

		data->id.idx = CN_TEST_IDX;
		data->id.val = CN_TEST_VAL;
		data->seq = seq++;
		data->ack = 0;
		data->len = 0;

		for (j=0; j<10; ++j) {
			for (i=0; i<1000; ++i) {
				len = netlink_send(s, data);
			}

			ulog("%d messages have been sent to %08x.%08x.\n", i, data->id.idx, data->id.val);
		}

		return 0;
	}


	pfd.fd = s;

	while (!need_exit) {
		pfd.events = POLLIN;
		pfd.revents = 0;
		switch (poll(&pfd, 1, -1)) {
			case 0:
				need_exit = 1;
				break;
			case -1:
				if (errno != EINTR) {
					need_exit = 1;
					break;
				}
				continue;
		}
		if (need_exit)
			break;

		memset(buf, 0, sizeof(buf));
		len = recv(s, buf, sizeof(buf), 0);
		if (len == -1) {
			perror("recv buf");
			close(s);
			return -1;
		}
		reply = (struct nlmsghdr *)buf;

		switch (reply->nlmsg_type) {
		case NLMSG_ERROR:
			fprintf(out, "Error message received.\n");
			fflush(out);
			break;
		case NLMSG_DONE:
			data = (struct cn_msg *)NLMSG_DATA(reply);

			time(&tm);
			fprintf(out, "%.24s : [%x.%x] [%08u.%08u].\n",
				ctime(&tm), data->id.idx, data->id.val, data->seq, data->ack);
			fflush(out);
			break;
		default:
			break;
		}
	}

	close(s);
	return 0;
}