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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; void* sin6_port; int /*<<< orphan*/  sin6_family; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; void* sin_port; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  addr6 ;
typedef  int /*<<< orphan*/  addr4 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 scalar_t__ cfg_do_ipv4 ; 
 scalar_t__ cfg_do_ipv6 ; 
 int /*<<< orphan*/  cfg_port ; 
 int /*<<< orphan*/  do_test (void*,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6addr_loopback ; 
 int /*<<< orphan*/  parse_opts (int,char**) ; 

int main(int argc, char **argv)
{
	parse_opts(argc, argv);

	if (cfg_do_ipv6) {
		struct sockaddr_in6 addr6 = {0};

		addr6.sin6_family = AF_INET6;
		addr6.sin6_port = htons(cfg_port);
		addr6.sin6_addr = in6addr_loopback;
		do_test((void *)&addr6, sizeof(addr6));
	}

	if (cfg_do_ipv4) {
		struct sockaddr_in addr4 = {0};

		addr4.sin_family = AF_INET;
		addr4.sin_port = htons(cfg_port);
		addr4.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		do_test((void *)&addr4, sizeof(addr4));
	}

	return 0;
}