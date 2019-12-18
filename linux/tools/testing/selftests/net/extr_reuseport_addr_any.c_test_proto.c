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

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ ESOCKTNOSUPPORT ; 
 int /*<<< orphan*/  IP4_ADDR ; 
 int /*<<< orphan*/  IP4_MAPPED6 ; 
 int /*<<< orphan*/  IP6_ADDR ; 
 int SOCK_DCCP ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (int,scalar_t__,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  run_one_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void test_proto(int proto, const char *proto_str)
{
	if (proto == SOCK_DCCP) {
		int test_fd;

		test_fd = socket(AF_INET, proto, 0);
		if (test_fd < 0) {
			if (errno == ESOCKTNOSUPPORT) {
				fprintf(stderr, "DCCP not supported: skipping DCCP tests\n");
				return;
			} else
				error(1, errno, "failed to create a DCCP socket");
		}
		close(test_fd);
	}

	fprintf(stderr, "%s IPv4 ... ", proto_str);
	run_one_test(AF_INET, AF_INET, proto, IP4_ADDR);

	fprintf(stderr, "%s IPv6 ... ", proto_str);
	run_one_test(AF_INET6, AF_INET6, proto, IP6_ADDR);

	fprintf(stderr, "%s IPv4 mapped to IPv6 ... ", proto_str);
	run_one_test(AF_INET, AF_INET6, proto, IP4_MAPPED6);
}