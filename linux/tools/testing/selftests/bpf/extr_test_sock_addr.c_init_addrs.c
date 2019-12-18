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
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct sock_addr_test {scalar_t__ expected_src_ip; int /*<<< orphan*/  domain; int /*<<< orphan*/  requested_port; scalar_t__ requested_ip; int /*<<< orphan*/  expected_port; scalar_t__ expected_ip; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int mk_sockaddr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct sockaddr*,int) ; 

__attribute__((used)) static int init_addrs(const struct sock_addr_test *test,
		      struct sockaddr_storage *requested_addr,
		      struct sockaddr_storage *expected_addr,
		      struct sockaddr_storage *expected_src_addr)
{
	socklen_t addr_len = sizeof(struct sockaddr_storage);

	if (mk_sockaddr(test->domain, test->expected_ip, test->expected_port,
			(struct sockaddr *)expected_addr, addr_len) == -1)
		goto err;

	if (mk_sockaddr(test->domain, test->requested_ip, test->requested_port,
			(struct sockaddr *)requested_addr, addr_len) == -1)
		goto err;

	if (test->expected_src_ip &&
	    mk_sockaddr(test->domain, test->expected_src_ip, 0,
			(struct sockaddr *)expected_src_addr, addr_len) == -1)
		goto err;

	return 0;
err:
	return -1;
}