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
struct sockaddr_in6 {scalar_t__ sin6_port; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int bind (int,struct sockaddr const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  in6addr_loopback ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in6*,int /*<<< orphan*/ ,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_server(void)
{
	struct sockaddr_in6 addr;
	int fd;

	fd = socket(AF_INET6, SOCK_STREAM, 0);
	if (fd == -1) {
		log_err("Failed to create server socket");
		goto out;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin6_family = AF_INET6;
	addr.sin6_addr = in6addr_loopback;
	addr.sin6_port = 0;

	if (bind(fd, (const struct sockaddr *)&addr, sizeof(addr)) == -1) {
		log_err("Failed to bind server socket");
		goto close_out;
	}

	if (listen(fd, 128) == -1) {
		log_err("Failed to listen on server socket");
		goto close_out;
	}

	goto out;

close_out:
	close(fd);
	fd = -1;
out:
	return fd;
}