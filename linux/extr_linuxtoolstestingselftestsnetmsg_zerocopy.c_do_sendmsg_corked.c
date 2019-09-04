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
struct msghdr {TYPE_1__* msg_iov; } ;
struct TYPE_4__ {scalar_t__ ss_family; } ;
struct TYPE_3__ {int iov_len; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  UDP_CORK ; 
 int cfg_cork ; 
 scalar_t__ cfg_cork_mixed ; 
 TYPE_2__ cfg_dst_addr ; 
 int cfg_payload_len ; 
 int cfg_zerocopy ; 
 int /*<<< orphan*/  do_sendmsg (int,struct msghdr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void do_sendmsg_corked(int fd, struct msghdr *msg)
{
	bool do_zerocopy = cfg_zerocopy;
	int i, payload_len, extra_len;

	/* split up the packet. for non-multiple, make first buffer longer */
	payload_len = cfg_payload_len / cfg_cork;
	extra_len = cfg_payload_len - (cfg_cork * payload_len);

	do_setsockopt(fd, IPPROTO_UDP, UDP_CORK, 1);

	for (i = 0; i < cfg_cork; i++) {

		/* in mixed-frags mode, alternate zerocopy and copy frags
		 * start with non-zerocopy, to ensure attach later works
		 */
		if (cfg_cork_mixed)
			do_zerocopy = (i & 1);

		msg->msg_iov[0].iov_len = payload_len + extra_len;
		extra_len = 0;

		do_sendmsg(fd, msg, do_zerocopy,
			   (cfg_dst_addr.ss_family == AF_INET ?
			    PF_INET : PF_INET6));
	}

	do_setsockopt(fd, IPPROTO_UDP, UDP_CORK, 0);
}