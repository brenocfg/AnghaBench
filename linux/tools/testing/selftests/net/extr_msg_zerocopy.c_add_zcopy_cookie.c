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
typedef  int /*<<< orphan*/  uint32_t ;
struct msghdr {scalar_t__ msg_control; } ;
struct cmsghdr {int /*<<< orphan*/  cmsg_type; int /*<<< orphan*/  cmsg_level; int /*<<< orphan*/  cmsg_len; } ;
typedef  int /*<<< orphan*/  cookie ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DATA (struct cmsghdr*) ; 
 int /*<<< orphan*/  CMSG_LEN (int) ; 
 int /*<<< orphan*/  RDS_CMSG_ZCOPY_COOKIE ; 
 int /*<<< orphan*/  SOL_RDS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void add_zcopy_cookie(struct msghdr *msg, uint32_t cookie)
{
	struct cmsghdr *cm;

	if (!msg->msg_control)
		error(1, errno, "NULL cookie");
	cm = (void *)msg->msg_control;
	cm->cmsg_len = CMSG_LEN(sizeof(cookie));
	cm->cmsg_level = SOL_RDS;
	cm->cmsg_type = RDS_CMSG_ZCOPY_COOKIE;
	memcpy(CMSG_DATA(cm), &cookie, sizeof(cookie));
}