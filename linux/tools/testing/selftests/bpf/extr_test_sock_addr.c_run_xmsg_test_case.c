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
struct sock_addr_test {scalar_t__ type; } ;
typedef  int socklen_t ;

/* Variables and functions */
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ cmp_addr (struct sockaddr_storage*,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 scalar_t__ init_addrs (struct sock_addr_test const*,struct sockaddr_storage*,struct sockaddr_storage*,struct sockaddr_storage*) ; 
 int recvmsg_from_client (int,struct sockaddr_storage*) ; 
 int sendmsg_to_server (scalar_t__,struct sockaddr_storage*,int,int,int /*<<< orphan*/ ,int*) ; 
 int start_server (scalar_t__,struct sockaddr_storage*,int) ; 

__attribute__((used)) static int run_xmsg_test_case(const struct sock_addr_test *test, int max_cmsg)
{
	socklen_t addr_len = sizeof(struct sockaddr_storage);
	struct sockaddr_storage expected_addr;
	struct sockaddr_storage server_addr;
	struct sockaddr_storage sendmsg_addr;
	struct sockaddr_storage recvmsg_addr;
	int clientfd = -1;
	int servfd = -1;
	int set_cmsg;
	int err = 0;

	if (test->type != SOCK_DGRAM)
		goto err;

	if (init_addrs(test, &sendmsg_addr, &server_addr, &expected_addr))
		goto err;

	/* Prepare server to sendmsg to */
	servfd = start_server(test->type, &server_addr, addr_len);
	if (servfd == -1)
		goto err;

	for (set_cmsg = 0; set_cmsg <= max_cmsg; ++set_cmsg) {
		if (clientfd >= 0)
			close(clientfd);

		clientfd = sendmsg_to_server(test->type, &sendmsg_addr,
					     addr_len, set_cmsg, /*flags*/0,
					     &err);
		if (err)
			goto out;
		else if (clientfd == -1)
			goto err;

		/* Try to receive message on server instead of using
		 * getpeername(2) on client socket, to check that client's
		 * destination address was rewritten properly, since
		 * getpeername(2) doesn't work with unconnected datagram
		 * sockets.
		 *
		 * Get source address from recvmsg(2) as well to make sure
		 * source was rewritten properly: getsockname(2) can't be used
		 * since socket is unconnected and source defined for one
		 * specific packet may differ from the one used by default and
		 * returned by getsockname(2).
		 */
		if (recvmsg_from_client(servfd, &recvmsg_addr) == -1)
			goto err;

		if (cmp_addr(&recvmsg_addr, &expected_addr, /*cmp_port*/0))
			goto err;
	}

	goto out;
err:
	err = -1;
out:
	close(clientfd);
	close(servfd);
	return err;
}