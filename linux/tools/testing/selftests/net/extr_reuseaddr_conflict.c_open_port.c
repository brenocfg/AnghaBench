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
typedef  int /*<<< orphan*/  v6only ;
struct sockaddr_in6 {int sin6_family; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_family; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  reuseaddr ;
typedef  int /*<<< orphan*/  addr6 ;
typedef  int /*<<< orphan*/  addr4 ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int /*<<< orphan*/  PORT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in6addr_any ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int open_port(int ipv6, int any)
{
	int fd = -1;
	int reuseaddr = 1;
	int v6only = 1;
	int addrlen;
	int ret = -1;
	struct sockaddr *addr;
	int family = ipv6 ? AF_INET6 : AF_INET;

	struct sockaddr_in6 addr6 = {
		.sin6_family = AF_INET6,
		.sin6_port = htons(PORT),
		.sin6_addr = in6addr_any
	};
	struct sockaddr_in addr4 = {
		.sin_family = AF_INET,
		.sin_port = htons(PORT),
		.sin_addr.s_addr = any ? htonl(INADDR_ANY) : inet_addr("127.0.0.1"),
	};


	if (ipv6) {
		addr = (struct sockaddr*)&addr6;
		addrlen = sizeof(addr6);
	} else {
		addr = (struct sockaddr*)&addr4;
		addrlen = sizeof(addr4);
	}

	if ((fd = socket(family, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket");
		goto out;
	}

	if (ipv6 && setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, (void*)&v6only,
			       sizeof(v6only)) < 0) {
		perror("setsockopt IPV6_V6ONLY");
		goto out;
	}

	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr,
		       sizeof(reuseaddr)) < 0) {
		perror("setsockopt SO_REUSEADDR");
		goto out;
	}

	if (bind(fd, addr, addrlen) < 0) {
		perror("bind");
		goto out;
	}

	if (any)
		return fd;

	if (listen(fd, 1) < 0) {
		perror("listen");
		goto out;
	}
	return fd;
out:
	close(fd);
	return ret;
}