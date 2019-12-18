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
typedef  scalar_t__ u8 ;
struct tomoyo_addr_info {unsigned int protocol; int /*<<< orphan*/  operation; } ;
struct socket {unsigned int type; TYPE_1__* ops; int /*<<< orphan*/  sk; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_2__ {int (* getname ) (struct socket*,struct sockaddr*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ const PF_UNIX ; 
 unsigned int const SOCK_SEQPACKET ; 
 unsigned int const SOCK_STREAM ; 
 int /*<<< orphan*/  TOMOYO_NETWORK_LISTEN ; 
 int stub1 (struct socket*,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int tomoyo_check_inet_address (struct sockaddr*,int,int /*<<< orphan*/ ,struct tomoyo_addr_info*) ; 
 int tomoyo_check_unix_address (struct sockaddr*,int,struct tomoyo_addr_info*) ; 
 scalar_t__ tomoyo_sock_family (int /*<<< orphan*/ ) ; 

int tomoyo_socket_listen_permission(struct socket *sock)
{
	struct tomoyo_addr_info address;
	const u8 family = tomoyo_sock_family(sock->sk);
	const unsigned int type = sock->type;
	struct sockaddr_storage addr;
	int addr_len;

	if (!family || (type != SOCK_STREAM && type != SOCK_SEQPACKET))
		return 0;
	{
		const int error = sock->ops->getname(sock, (struct sockaddr *)
						     &addr, 0);

		if (error < 0)
			return error;
		addr_len = error;
	}
	address.protocol = type;
	address.operation = TOMOYO_NETWORK_LISTEN;
	if (family == PF_UNIX)
		return tomoyo_check_unix_address((struct sockaddr *) &addr,
						 addr_len, &address);
	return tomoyo_check_inet_address((struct sockaddr *) &addr, addr_len,
					 0, &address);
}