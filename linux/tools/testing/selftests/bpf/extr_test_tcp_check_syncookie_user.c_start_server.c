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
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_STREAM ; 
 int bind (int,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_server(const struct sockaddr *addr, socklen_t len)
{
	int fd;

	fd = socket(addr->sa_family, SOCK_STREAM, 0);
	if (fd == -1) {
		log_err("Failed to create server socket");
		goto out;
	}

	if (bind(fd, addr, len) == -1) {
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