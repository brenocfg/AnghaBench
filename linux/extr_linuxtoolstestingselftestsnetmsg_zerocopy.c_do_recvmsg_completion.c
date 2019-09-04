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
struct rds_zcopy_cookies {int dummy; } ;
struct msghdr {char* msg_control; int msg_controllen; int msg_flags; } ;
struct cmsghdr {scalar_t__ cmsg_level; scalar_t__ cmsg_type; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  cmsgbuf ;

/* Variables and functions */
 scalar_t__ CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 int CMSG_SPACE (int) ; 
 int MSG_CTRUNC ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 scalar_t__ RDS_CMSG_ZCOPY_COMPLETION ; 
 scalar_t__ SOL_RDS ; 
 int /*<<< orphan*/  completions ; 
 scalar_t__ do_process_zerocopy_cookies (struct rds_zcopy_cookies*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (struct msghdr*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ recvmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool do_recvmsg_completion(int fd)
{
	char cmsgbuf[CMSG_SPACE(sizeof(struct rds_zcopy_cookies))];
	struct rds_zcopy_cookies *ck;
	struct cmsghdr *cmsg;
	struct msghdr msg;
	bool ret = false;

	memset(&msg, 0, sizeof(msg));
	msg.msg_control = cmsgbuf;
	msg.msg_controllen = sizeof(cmsgbuf);

	if (recvmsg(fd, &msg, MSG_DONTWAIT))
		return ret;

	if (msg.msg_flags & MSG_CTRUNC)
		error(1, errno, "recvmsg notification: truncated");

	for (cmsg = CMSG_FIRSTHDR(&msg); cmsg; cmsg = CMSG_NXTHDR(&msg, cmsg)) {
		if (cmsg->cmsg_level == SOL_RDS &&
		    cmsg->cmsg_type == RDS_CMSG_ZCOPY_COMPLETION) {

			ck = (struct rds_zcopy_cookies *)CMSG_DATA(cmsg);
			completions += do_process_zerocopy_cookies(ck);
			ret = true;
			break;
		}
		error(0, 0, "ignoring cmsg at level %d type %d\n",
			    cmsg->cmsg_level, cmsg->cmsg_type);
	}
	return ret;
}