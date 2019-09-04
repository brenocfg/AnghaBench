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
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  dst ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  LINKLOCAL_MULTICAST ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ mk_dst_addr (int /*<<< orphan*/ ,char const*,struct sockaddr_in6*) ; 
 int sendto (int,char**,int,int /*<<< orphan*/ ,struct sockaddr const*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_packet(const char *iface)
{
	struct sockaddr_in6 dst;
	char msg[] = "msg";
	int err = 0;
	int fd = -1;

	if (mk_dst_addr(LINKLOCAL_MULTICAST, iface, &dst))
		goto err;

	fd = socket(AF_INET6, SOCK_DGRAM, 0);
	if (fd == -1) {
		log_err("Failed to create UDP socket");
		goto err;
	}

	if (sendto(fd, &msg, sizeof(msg), 0, (const struct sockaddr *)&dst,
		   sizeof(dst)) == -1) {
		log_err("Failed to send datagram");
		goto err;
	}

	goto out;
err:
	err = -1;
out:
	if (fd >= 0)
		close(fd);
	return err;
}