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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int ENOPROTOOPT ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  INADDR_ANY ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 char* RPCBIND_NETID_TCP ; 
 char* RPCBIND_NETID_UDP ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (unsigned short const) ; 
 int rpcb_register (struct net*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,unsigned short const,unsigned short const) ; 
 int rpcb_v4_register (struct net*,int /*<<< orphan*/  const,int /*<<< orphan*/  const,struct sockaddr const*,char const*) ; 

__attribute__((used)) static int __svc_rpcb_register4(struct net *net, const u32 program,
				const u32 version,
				const unsigned short protocol,
				const unsigned short port)
{
	const struct sockaddr_in sin = {
		.sin_family		= AF_INET,
		.sin_addr.s_addr	= htonl(INADDR_ANY),
		.sin_port		= htons(port),
	};
	const char *netid;
	int error;

	switch (protocol) {
	case IPPROTO_UDP:
		netid = RPCBIND_NETID_UDP;
		break;
	case IPPROTO_TCP:
		netid = RPCBIND_NETID_TCP;
		break;
	default:
		return -ENOPROTOOPT;
	}

	error = rpcb_v4_register(net, program, version,
					(const struct sockaddr *)&sin, netid);

	/*
	 * User space didn't support rpcbind v4, so retry this
	 * registration request with the legacy rpcbind v2 protocol.
	 */
	if (error == -EPROTONOSUPPORT)
		error = rpcb_register(net, program, version, protocol, port);

	return error;
}