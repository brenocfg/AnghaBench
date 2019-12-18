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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct sockcm_cookie {int mark; int tsflags; int /*<<< orphan*/  transmit_time; } ;
struct sock {int dummy; } ;
struct msghdr {int dummy; } ;
struct cmsghdr {int cmsg_type; int /*<<< orphan*/  cmsg_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  user_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 int /*<<< orphan*/  CMSG_LEN (int) ; 
 int EINVAL ; 
 int EPERM ; 
#define  SCM_CREDENTIALS 132 
#define  SCM_RIGHTS 131 
#define  SCM_TXTIME 130 
 int /*<<< orphan*/  SOCK_TXTIME ; 
 int SOF_TIMESTAMPING_TX_RECORD_MASK ; 
#define  SO_MARK 129 
#define  SO_TIMESTAMPING_OLD 128 
 int /*<<< orphan*/  get_unaligned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ns_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 TYPE_1__* sock_net (struct sock*) ; 

int __sock_cmsg_send(struct sock *sk, struct msghdr *msg, struct cmsghdr *cmsg,
		     struct sockcm_cookie *sockc)
{
	u32 tsflags;

	switch (cmsg->cmsg_type) {
	case SO_MARK:
		if (!ns_capable(sock_net(sk)->user_ns, CAP_NET_ADMIN))
			return -EPERM;
		if (cmsg->cmsg_len != CMSG_LEN(sizeof(u32)))
			return -EINVAL;
		sockc->mark = *(u32 *)CMSG_DATA(cmsg);
		break;
	case SO_TIMESTAMPING_OLD:
		if (cmsg->cmsg_len != CMSG_LEN(sizeof(u32)))
			return -EINVAL;

		tsflags = *(u32 *)CMSG_DATA(cmsg);
		if (tsflags & ~SOF_TIMESTAMPING_TX_RECORD_MASK)
			return -EINVAL;

		sockc->tsflags &= ~SOF_TIMESTAMPING_TX_RECORD_MASK;
		sockc->tsflags |= tsflags;
		break;
	case SCM_TXTIME:
		if (!sock_flag(sk, SOCK_TXTIME))
			return -EINVAL;
		if (cmsg->cmsg_len != CMSG_LEN(sizeof(u64)))
			return -EINVAL;
		sockc->transmit_time = get_unaligned((u64 *)CMSG_DATA(cmsg));
		break;
	/* SCM_RIGHTS and SCM_CREDENTIALS are semantically in SOL_UNIX. */
	case SCM_RIGHTS:
	case SCM_CREDENTIALS:
		break;
	default:
		return -EINVAL;
	}
	return 0;
}