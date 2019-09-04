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
struct sockaddr_nl {int /*<<< orphan*/  nl_family; } ;
struct sockaddr {int dummy; } ;
struct nlattr {scalar_t__ nla_len; void* nla_type; } ;
struct TYPE_4__ {int nlmsg_len; int /*<<< orphan*/  nlmsg_pid; scalar_t__ nlmsg_seq; int /*<<< orphan*/  nlmsg_flags; void* nlmsg_type; } ;
struct TYPE_3__ {int version; int /*<<< orphan*/  cmd; } ;
struct msgtemplate {TYPE_2__ n; TYPE_1__ g; } ;
typedef  int /*<<< orphan*/  nladdr ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  void* __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NETLINK ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ GENLMSG_DATA (struct msgtemplate*) ; 
 int /*<<< orphan*/  GENL_HDRLEN ; 
 int /*<<< orphan*/  NLA_DATA (struct nlattr*) ; 
 scalar_t__ NLA_HDRLEN ; 
 scalar_t__ NLMSG_ALIGN (scalar_t__) ; 
 int NLMSG_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_REQUEST ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_nl*,int /*<<< orphan*/ ,int) ; 
 int sendto (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 

__attribute__((used)) static int send_cmd(int sd, __u16 nlmsg_type, __u32 nlmsg_pid,
	     __u8 genl_cmd, __u16 nla_type,
	     void *nla_data, int nla_len)
{
	struct nlattr *na;
	struct sockaddr_nl nladdr;
	int r, buflen;
	char *buf;

	struct msgtemplate msg;

	msg.n.nlmsg_len = NLMSG_LENGTH(GENL_HDRLEN);
	msg.n.nlmsg_type = nlmsg_type;
	msg.n.nlmsg_flags = NLM_F_REQUEST;
	msg.n.nlmsg_seq = 0;
	msg.n.nlmsg_pid = nlmsg_pid;
	msg.g.cmd = genl_cmd;
	msg.g.version = 0x1;
	na = (struct nlattr *) GENLMSG_DATA(&msg);
	na->nla_type = nla_type;
	na->nla_len = nla_len + 1 + NLA_HDRLEN;
	memcpy(NLA_DATA(na), nla_data, nla_len);
	msg.n.nlmsg_len += NLMSG_ALIGN(na->nla_len);

	buf = (char *) &msg;
	buflen = msg.n.nlmsg_len ;
	memset(&nladdr, 0, sizeof(nladdr));
	nladdr.nl_family = AF_NETLINK;
	while ((r = sendto(sd, buf, buflen, 0, (struct sockaddr *) &nladdr,
			   sizeof(nladdr))) < buflen) {
		if (r > 0) {
			buf += r;
			buflen -= r;
		} else if (errno != EAGAIN)
			return -1;
	}
	return 0;
}