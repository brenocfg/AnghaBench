#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_4__ {scalar_t__ buf; } ;
struct TYPE_5__ {TYPE_1__ xp_rtaddr; int /*<<< orphan*/  xp_fd; } ;
typedef  TYPE_2__ SVCXPRT ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 int getpeereid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
__rpc_get_local_uid(SVCXPRT *transp, uid_t *uid) {
	SOCKET sock;
	int ret;
	gid_t egid;
	uid_t euid;
	struct sockaddr *sa;

	sock = transp->xp_fd;
	sa = (struct sockaddr *)transp->xp_rtaddr.buf;
	if (sa->sa_family == AF_UNIX) {
		ret = getpeereid(sock, &euid, &egid);
		if (ret == 0)
			*uid = euid;
		return (ret);
	} else
		return (-1);
}