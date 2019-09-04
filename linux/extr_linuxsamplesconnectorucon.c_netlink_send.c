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
struct nlmsghdr {unsigned int nlmsg_len; scalar_t__ nlmsg_flags; int /*<<< orphan*/  nlmsg_type; int /*<<< orphan*/  nlmsg_pid; scalar_t__ nlmsg_seq; } ;
struct cn_msg {scalar_t__ len; } ;

/* Variables and functions */
 struct cn_msg* NLMSG_DATA (struct nlmsghdr*) ; 
 int /*<<< orphan*/  NLMSG_DONE ; 
 unsigned int NLMSG_SPACE (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  memcpy (struct cn_msg*,struct cn_msg*,scalar_t__) ; 
 int send (int,struct nlmsghdr*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ulog (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netlink_send(int s, struct cn_msg *msg)
{
	struct nlmsghdr *nlh;
	unsigned int size;
	int err;
	char buf[128];
	struct cn_msg *m;

	size = NLMSG_SPACE(sizeof(struct cn_msg) + msg->len);

	nlh = (struct nlmsghdr *)buf;
	nlh->nlmsg_seq = seq++;
	nlh->nlmsg_pid = getpid();
	nlh->nlmsg_type = NLMSG_DONE;
	nlh->nlmsg_len = size;
	nlh->nlmsg_flags = 0;

	m = NLMSG_DATA(nlh);
#if 0
	ulog("%s: [%08x.%08x] len=%u, seq=%u, ack=%u.\n",
	       __func__, msg->id.idx, msg->id.val, msg->len, msg->seq, msg->ack);
#endif
	memcpy(m, msg, sizeof(*m) + msg->len);

	err = send(s, nlh, size, 0);
	if (err == -1)
		ulog("Failed to send: %s [%d].\n",
			strerror(errno), errno);

	return err;
}