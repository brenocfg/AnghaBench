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
typedef  int /*<<< orphan*/  tv ;
struct timeval {int tv_usec; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  raddr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVTIMEO ; 
 scalar_t__ bind (int,void*,int) ; 
 int /*<<< orphan*/  cfg_port ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_rx(void)
{
	struct timeval tv = { .tv_usec = 100 * 1000 };
	struct sockaddr_in raddr = {0};
	int fd;

	fd = socket(PF_INET, SOCK_DGRAM, 0);
	if (fd == -1)
		error(1, errno, "socket r");

	if (setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)))
		error(1, errno, "setsockopt rcv timeout");

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(cfg_port);
	raddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(fd, (void *)&raddr, sizeof(raddr)))
		error(1, errno, "bind r");

	return fd;
}