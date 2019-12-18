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
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ connect (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setsockopt_txtime (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_tx(struct sockaddr *addr, socklen_t alen)
{
	int fd;

	fd = socket(addr->sa_family, SOCK_DGRAM, 0);
	if (fd == -1)
		error(1, errno, "socket t");

	if (connect(fd, addr, alen))
		error(1, errno, "connect");

	setsockopt_txtime(fd);

	return fd;
}