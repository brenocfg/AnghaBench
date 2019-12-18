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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  int /*<<< orphan*/  addrstr ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_ntop (scalar_t__,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  log_msg (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ quiet ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void log_address(const char *desc, struct sockaddr *sa)
{
	char addrstr[64];

	if (quiet)
		return;

	if (sa->sa_family == AF_INET) {
		struct sockaddr_in *s = (struct sockaddr_in *) sa;

		log_msg("%s %s:%d",
			desc,
			inet_ntop(AF_INET, &s->sin_addr, addrstr,
				  sizeof(addrstr)),
			ntohs(s->sin_port));

	} else if (sa->sa_family == AF_INET6) {
		struct sockaddr_in6 *s6 = (struct sockaddr_in6 *) sa;

		log_msg("%s [%s]:%d",
			desc,
			inet_ntop(AF_INET6, &s6->sin6_addr, addrstr,
				  sizeof(addrstr)),
			ntohs(s6->sin6_port));
	}

	printf("\n");

	fflush(stdout);
}