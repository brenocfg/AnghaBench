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
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 
 int /*<<< orphan*/  msg ; 
 int /*<<< orphan*/  msglen ; 
 int sendto (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_broadcast (int) ; 
 scalar_t__ try_broadcast ; 

__attribute__((used)) static int send_msg_no_cmsg(int sd, void *addr, socklen_t alen)
{
	int err;

again:
	err = sendto(sd, msg, msglen, 0, addr, alen);
	if (err < 0) {
		if (errno == EACCES && try_broadcast) {
			try_broadcast = 0;
			if (!set_broadcast(sd))
				goto again;
			errno = EACCES;
		}

		log_err_errno("sendto failed");
		return 1;
	}

	return 0;
}