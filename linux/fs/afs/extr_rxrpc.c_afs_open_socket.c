#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_1__* sk; } ;
struct TYPE_5__ {scalar_t__ sin6_port; int /*<<< orphan*/  sin6_family; } ;
struct TYPE_6__ {TYPE_2__ sin6; } ;
struct sockaddr_rxrpc {int transport_len; int /*<<< orphan*/  srx_service; TYPE_3__ transport; int /*<<< orphan*/  transport_type; int /*<<< orphan*/  srx_family; } ;
struct sockaddr {int dummy; } ;
struct afs_net {int /*<<< orphan*/  charge_preallocation_work; struct socket* socket; int /*<<< orphan*/  net; } ;
typedef  int /*<<< orphan*/  srx ;
typedef  int /*<<< orphan*/  min_level ;
struct TYPE_4__ {int /*<<< orphan*/  sk_allocation; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_CM_PORT ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AF_RXRPC ; 
 int /*<<< orphan*/  CM_SERVICE ; 
 int EADDRINUSE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  RXRPC_MIN_SECURITY_LEVEL ; 
 unsigned int RXRPC_SECURITY_ENCRYPT ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_RXRPC ; 
 int /*<<< orphan*/  YFS_CM_SERVICE ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  afs_charge_preallocation (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  afs_rx_discard_new_call ; 
 int /*<<< orphan*/  afs_rx_new_call ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int kernel_bind (struct socket*,struct sockaddr*,int) ; 
 int kernel_listen (struct socket*,int /*<<< orphan*/ ) ; 
 int kernel_setsockopt (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_rxrpc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rxrpc_kernel_new_call_notification (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sock_create_kern (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct socket**) ; 
 int /*<<< orphan*/  sock_release (struct socket*) ; 

int afs_open_socket(struct afs_net *net)
{
	struct sockaddr_rxrpc srx;
	struct socket *socket;
	unsigned int min_level;
	int ret;

	_enter("");

	ret = sock_create_kern(net->net, AF_RXRPC, SOCK_DGRAM, PF_INET6, &socket);
	if (ret < 0)
		goto error_1;

	socket->sk->sk_allocation = GFP_NOFS;

	/* bind the callback manager's address to make this a server socket */
	memset(&srx, 0, sizeof(srx));
	srx.srx_family			= AF_RXRPC;
	srx.srx_service			= CM_SERVICE;
	srx.transport_type		= SOCK_DGRAM;
	srx.transport_len		= sizeof(srx.transport.sin6);
	srx.transport.sin6.sin6_family	= AF_INET6;
	srx.transport.sin6.sin6_port	= htons(AFS_CM_PORT);

	min_level = RXRPC_SECURITY_ENCRYPT;
	ret = kernel_setsockopt(socket, SOL_RXRPC, RXRPC_MIN_SECURITY_LEVEL,
				(void *)&min_level, sizeof(min_level));
	if (ret < 0)
		goto error_2;

	ret = kernel_bind(socket, (struct sockaddr *) &srx, sizeof(srx));
	if (ret == -EADDRINUSE) {
		srx.transport.sin6.sin6_port = 0;
		ret = kernel_bind(socket, (struct sockaddr *) &srx, sizeof(srx));
	}
	if (ret < 0)
		goto error_2;

	srx.srx_service = YFS_CM_SERVICE;
	ret = kernel_bind(socket, (struct sockaddr *) &srx, sizeof(srx));
	if (ret < 0)
		goto error_2;

	/* Ideally, we'd turn on service upgrade here, but we can't because
	 * OpenAFS is buggy and leaks the userStatus field from packet to
	 * packet and between FS packets and CB packets - so if we try to do an
	 * upgrade on an FS packet, OpenAFS will leak that into the CB packet
	 * it sends back to us.
	 */

	rxrpc_kernel_new_call_notification(socket, afs_rx_new_call,
					   afs_rx_discard_new_call);

	ret = kernel_listen(socket, INT_MAX);
	if (ret < 0)
		goto error_2;

	net->socket = socket;
	afs_charge_preallocation(&net->charge_preallocation_work);
	_leave(" = 0");
	return 0;

error_2:
	sock_release(socket);
error_1:
	_leave(" = %d", ret);
	return ret;
}