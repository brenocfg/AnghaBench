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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr {int dummy; } ;
struct sock_args {int /*<<< orphan*/  expected_raddr; scalar_t__ has_expected_raddr; int /*<<< orphan*/  expected_laddr; scalar_t__ has_expected_laddr; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  local_addr ;

/* Variables and functions */
 int expected_addr_match (struct sockaddr*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ getpeername (int,struct sockaddr*,int*) ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  log_address (char const*,struct sockaddr*) ; 
 int /*<<< orphan*/  log_err_errno (char*) ; 
 scalar_t__ server_mode ; 

__attribute__((used)) static int show_sockstat(int sd, struct sock_args *args)
{
	struct sockaddr_in6 local_addr, remote_addr;
	socklen_t alen = sizeof(local_addr);
	struct sockaddr *sa;
	const char *desc;
	int rc = 0;

	desc = server_mode ? "server local:" : "client local:";
	sa = (struct sockaddr *) &local_addr;
	if (getsockname(sd, sa, &alen) == 0) {
		log_address(desc, sa);

		if (args->has_expected_laddr) {
			rc = expected_addr_match(sa, &args->expected_laddr,
						 "local");
		}
	} else {
		log_err_errno("getsockname failed");
	}

	sa = (struct sockaddr *) &remote_addr;
	desc = server_mode ? "server peer:" : "client peer:";
	if (getpeername(sd, sa, &alen) == 0) {
		log_address(desc, sa);

		if (args->has_expected_raddr) {
			rc |= expected_addr_match(sa, &args->expected_raddr,
						 "remote");
		}
	} else {
		log_err_errno("getpeername failed");
	}

	return rc;
}