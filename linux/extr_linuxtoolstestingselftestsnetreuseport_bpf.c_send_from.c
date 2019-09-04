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
typedef  int /*<<< orphan*/  uint16_t ;
struct test_params {int /*<<< orphan*/  protocol; int /*<<< orphan*/  send_family; int /*<<< orphan*/  recv_port; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  one ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_FASTOPEN ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (int const,struct sockaddr* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int const) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct sockaddr* const) ; 
 struct sockaddr* new_any_sockaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sockaddr* new_loopback_sockaddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sendto (int const,char*,size_t,int /*<<< orphan*/ ,struct sockaddr* const,int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  sockaddr_size () ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_from(struct test_params p, uint16_t sport, char *buf,
		      size_t len)
{
	struct sockaddr * const saddr = new_any_sockaddr(p.send_family, sport);
	struct sockaddr * const daddr =
		new_loopback_sockaddr(p.send_family, p.recv_port);
	const int fd = socket(p.send_family, p.protocol, 0), one = 1;

	if (fd < 0)
		error(1, errno, "failed to create send socket");

	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)))
		error(1, errno, "failed to set reuseaddr");

	if (bind(fd, saddr, sockaddr_size()))
		error(1, errno, "failed to bind send socket");

	if (sendto(fd, buf, len, MSG_FASTOPEN, daddr, sockaddr_size()) < 0)
		error(1, errno, "failed to send message");

	close(fd);
	free(saddr);
	free(daddr);
}