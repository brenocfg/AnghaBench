#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct ip_mreq {int /*<<< orphan*/  imr_multiaddr; struct in_addr imr_interface; int /*<<< orphan*/  member_0; } ;
typedef  int socklen_t ;
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/  bsd_socket; } ;
typedef  TYPE_1__ php_socket ;
typedef  int /*<<< orphan*/  mreq ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IP_ADD_MEMBERSHIP ; 
 int /*<<< orphan*/  IP_DROP_MEMBERSHIP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ php_if_index_to_addr4 (unsigned int,TYPE_1__*,struct in_addr*) ; 
 int setsockopt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int _php_mcast_join_leave(
	php_socket *sock,
	int level,
	struct sockaddr *group, /* struct sockaddr_in/sockaddr_in6 */
	socklen_t group_len,
	unsigned int if_index,
	int join)
{
#ifdef RFC3678_API
	struct group_req greq = {0};

	memcpy(&greq.gr_group, group, group_len);
	assert(greq.gr_group.ss_family != 0); /* the caller has set this */
	greq.gr_interface = if_index;

	return setsockopt(sock->bsd_socket, level,
			join ? MCAST_JOIN_GROUP : MCAST_LEAVE_GROUP, (char*)&greq,
			sizeof(greq));
#else
	if (sock->type == AF_INET) {
		struct ip_mreq mreq = {0};
		struct in_addr addr;

		assert(group_len == sizeof(struct sockaddr_in));

		if (if_index != 0) {
			if (php_if_index_to_addr4(if_index, sock, &addr) ==
					FAILURE)
				return -2; /* failure, but notice already emitted */
			mreq.imr_interface = addr;
		} else {
			mreq.imr_interface.s_addr = htonl(INADDR_ANY);
		}
		mreq.imr_multiaddr = ((struct sockaddr_in*)group)->sin_addr;
		return setsockopt(sock->bsd_socket, level,
				join ? IP_ADD_MEMBERSHIP : IP_DROP_MEMBERSHIP, (char*)&mreq,
				sizeof(mreq));
	}
#if HAVE_IPV6
	else if (sock->type == AF_INET6) {
		struct ipv6_mreq mreq = {0};

		assert(group_len == sizeof(struct sockaddr_in6));

		mreq.ipv6mr_multiaddr = ((struct sockaddr_in6*)group)->sin6_addr;
		mreq.ipv6mr_interface = if_index;

		return setsockopt(sock->bsd_socket, level,
				join ? IPV6_JOIN_GROUP : IPV6_LEAVE_GROUP, (char*)&mreq,
				sizeof(mreq));
	}
#endif
	else {
		php_error_docref(NULL, E_WARNING,
			"Option %s is inapplicable to this socket type",
			join ? "MCAST_JOIN_GROUP" : "MCAST_LEAVE_GROUP");
		return -2;
	}
#endif
}