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
struct msghdr {int msg_flags; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int MSG_CTRUNC ; 
 int MSG_ERRQUEUE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (int,scalar_t__,char*,...) ; 
 int recvmsg (int,struct msghdr*,int) ; 

__attribute__((used)) static void flush_zerocopy(int fd)
{
	struct msghdr msg = {0};	/* flush */
	int ret;

	while (1) {
		ret = recvmsg(fd, &msg, MSG_ERRQUEUE);
		if (ret == -1 && errno == EAGAIN)
			break;
		if (ret == -1)
			error(1, errno, "errqueue");
		if (msg.msg_flags != (MSG_ERRQUEUE | MSG_CTRUNC))
			error(1, 0, "errqueue: flags 0x%x\n", msg.msg_flags);
		msg.msg_flags = 0;
	}
}