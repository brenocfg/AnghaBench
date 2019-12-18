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
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr {int dummy; } ;
struct __rpc_sockinfo {int si_alen; scalar_t__ si_af; int si_proto; int si_socktype; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  proto_info ;
struct TYPE_2__ {int iMaxSockAddr; scalar_t__ iAddressFamily; } ;
typedef  TYPE_1__ WSAPROTOCOL_INFO ;
typedef  int /*<<< orphan*/  SOCKET ;
typedef  scalar_t__ ADDRESS_FAMILY ;

/* Variables and functions */
 scalar_t__ AF_LOCAL ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 scalar_t__ SOCKET_ERROR ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_PROTOCOL_INFO ; 
 int /*<<< orphan*/  SO_TYPE ; 
 int WSAGetLastError () ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 scalar_t__ getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

int
__rpc_fd2sockinfo(SOCKET fd, struct __rpc_sockinfo *sip)
{
	socklen_t len;
	int type, proto;
	struct sockaddr_storage ss;

#ifdef _WIN32
	WSAPROTOCOL_INFO proto_info;
	int proto_info_size = sizeof(proto_info);
	if (getsockopt(fd, SOL_SOCKET, SO_PROTOCOL_INFO, (char *)&proto_info, &proto_info_size) == SOCKET_ERROR) {
#ifndef __REACTOS__
		int err = WSAGetLastError();
#endif
		return 0;
	}
	len = proto_info.iMaxSockAddr;
	ss.ss_family = (ADDRESS_FAMILY)proto_info.iAddressFamily;
#else
	len = sizeof ss;
	if (getsockname(fd, (struct sockaddr *)&ss, &len) == SOCKET_ERROR) {
		return 0;
	}
#endif
	sip->si_alen = len;

	len = sizeof type;
	if (getsockopt(fd, SOL_SOCKET, SO_TYPE, (char *)&type, &len) == SOCKET_ERROR) {
#ifndef __REACTOS__
		int err = WSAGetLastError();
#endif
		return 0;
	}

	/* XXX */
#ifdef AF_LOCAL
	if (ss.ss_family != AF_LOCAL) {
#endif
		if (type == SOCK_STREAM)
			proto = IPPROTO_TCP;
		else if (type == SOCK_DGRAM)
			proto = IPPROTO_UDP;
		else
			return 0;
#ifdef AF_LOCAL
	} else
		proto = 0;
#endif

	sip->si_af = ss.ss_family;
	sip->si_proto = proto;
	sip->si_socktype = type;

	return 1;
}