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
struct sock_addr_test {int /*<<< orphan*/  type; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ cmp_local_addr (int,struct sockaddr_storage*) ; 
 int connect_to_server (int /*<<< orphan*/ ,struct sockaddr_storage*,int) ; 
 scalar_t__ init_addrs (struct sock_addr_test const*,struct sockaddr_storage*,struct sockaddr_storage*,int /*<<< orphan*/ *) ; 
 int start_server (int /*<<< orphan*/ ,struct sockaddr_storage*,int) ; 

__attribute__((used)) static int run_bind_test_case(const struct sock_addr_test *test)
{
	socklen_t addr_len = sizeof(struct sockaddr_storage);
	struct sockaddr_storage requested_addr;
	struct sockaddr_storage expected_addr;
	int clientfd = -1;
	int servfd = -1;
	int err = 0;

	if (init_addrs(test, &requested_addr, &expected_addr, NULL))
		goto err;

	servfd = start_server(test->type, &requested_addr, addr_len);
	if (servfd == -1)
		goto err;

	if (cmp_local_addr(servfd, &expected_addr))
		goto err;

	/* Try to connect to server just in case */
	clientfd = connect_to_server(test->type, &expected_addr, addr_len);
	if (clientfd == -1)
		goto err;

	goto out;
err:
	err = -1;
out:
	close(clientfd);
	close(servfd);
	return err;
}