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
struct sockaddr_storage {int /*<<< orphan*/  ss_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int SOCK_STREAM ; 
 int bind (int,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_server(int type, const struct sockaddr_storage *addr,
			socklen_t addr_len)
{
	int fd;

	fd = socket(addr->ss_family, type, 0);
	if (fd == -1) {
		log_err("Failed to create server socket");
		goto out;
	}

	if (bind(fd, (const struct sockaddr *)addr, addr_len) == -1) {
		log_err("Failed to bind server socket");
		goto close_out;
	}

	if (type == SOCK_STREAM) {
		if (listen(fd, 128) == -1) {
			log_err("Failed to listen on server socket");
			goto close_out;
		}
	}

	goto out;
close_out:
	close(fd);
	fd = -1;
out:
	return fd;
}