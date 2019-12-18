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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 int SOCK_STREAM ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 
 int /*<<< orphan*/  log_msg (char*,...) ; 
 int sendto (int,char*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_broadcast (int) ; 
 int /*<<< orphan*/  stdin ; 
 int strlen (char*) ; 
 scalar_t__ try_broadcast ; 
 scalar_t__ write (int,char*,int) ; 

__attribute__((used)) static int stdin_to_socket(int sd, int type, void *addr, socklen_t alen)
{
	char buf[1024];
	int len;

	if (fgets(buf, sizeof(buf), stdin) == NULL)
		return 0;

	len = strlen(buf);
	if (type == SOCK_STREAM) {
		if (write(sd, buf, len) < 0) {
			log_err_errno("failed to send buf");
			return -1;
		}
	} else {
		int err;

again:
		err = sendto(sd, buf, len, 0, addr, alen);
		if (err < 0) {
			if (errno == EACCES && try_broadcast) {
				try_broadcast = 0;
				if (!set_broadcast(sd))
					goto again;
				errno = EACCES;
			}
			log_err_errno("failed to send msg to peer");
			return -1;
		}
	}
	log_msg("Sent message:\n");
	log_msg("    %.24s%s\n", buf, len > 24 ? " ..." : "");

	return 1;
}